## Texture Mapping
For the first part of our final project, we implemented texture mapping to our renderer. The core idea behind texture mapping is that, when the fragment shader is deciding what color to use for each fragment, the shader pulls the surface color of the object or model from a 2D image (texture) that has been pre-loaded. Several parts needs to be put in place to execute on this idea.

Firstly, the texture needs to be loaded into the program. STB, an open source library, makes this easy. STB contains functions to load in several image formats so that OpenGL can interface them. Starting at line 155 in 'base.cpp' we load in our textures using STB, and then write them to a uniform buffer so that they may be accessed by the shaders in the GPU.

Secondly, the object file needs to define how a texture is to be mapped to each of its vertices. We added to our 'cube.obj' file several 'vt' tags, one for each vertex of the cube, that specified which coordinate of the texture should be mapped to that vertex. Here are the mappings we used

```
vt 1 1  //front bottom left corner
vt 1 0  //front upper left corner
vt 0 0  //front upper right corner
vt 0 1  //front bottom right corner

vt 0 0  //back bottom left corner
vt 0 1  //back upper left corner
vt 1 1  //back upper right corner
vt 1 0  //back bottom right corner
```

*There is one shortcoming of using these mappings, one that I will cover later in this section.

Then, after adding the new vt tags to our cube model, we needed to update our 'importObj()' and shader buffers to account for the added vertex texture data. If the imported model contained vt tags, those coordinates would be appropriately added to the output array of data. Additionally, we needed to create a buffer to hold that data, separate from the buffers already holding the vertex position data, color data, etc. 

Lastly, we needed to use the data in the texture and vertex buffers inside the fragment shader to correctly color the fragment. This is as easy as creating uniform and input variables in the fragment and vertex shader so that, in the fragment shader, we can run the following line of code to set the fragment color correctly:

```
    //texture1 is our loaded image texture
    //TexCoord is where on the image the current fragment should pull its color from
    //FragColor is the output value, the final color of the fragment.
    FragColor = texture(texture1, TexCoord);
```


### Wrapping texture around entire cube
One issue with implementing texture mapping we had was that, because our renderer was using indexed triangles to store the model data, where there is only one instance of a vertex for all the faces it is a part of, we could only assign one texture coordinate to each face. This is an issue because, in our effort to map copies of the same brick texture to each side of our cube, we would need to tell the same vertex to map to a different part of the texture for each face it is a part of. But we only have 1 instance of the vertex in the buffer. Therein lies the limitation, which to fix we would have had to revert our wavefront file parser and renderer to support the separated triangles method of storing model data.

One work-around we found was that we could stretch the existing texture around corners to cover all sides of the cube, shown below

[pic of rendered cube with brick texture]

There are 2 shortcomings with this work-around. 1) the texture is stretched and sheared in a visually obvious way, and 2) the lighting for the texture does not match the face it is projected too, so lighting is not accurate when the model is rotated.

## Normal Mapping
In the second part of our project, we implemented normal mapping. As normal maps are still textures, importing the normal map textures into the renderer and shaders is identical to the texture mapping part, so I will gloss over that for now. Inside the fragment shader, we combined our existing flat shading code with the normals of the normal map to achieve the textured brick wall appearance.

Our normal map assumes the default vector is (0,0,1), or a unit vector in the z direction. However, the face that the normal map is projected onto will not always be facing the z direction, so we need to create a rotation matrix to properly account for any rotation applied to the model. We create this matrix inside 'shaders/texturenormal.fs' with 

```
vec3 xTangent = dFdx(viewPos);
vec3 yTangent = dFdy(viewPos);
vec3 faceNormal = normalize(cross(xTangent, yTangent));
vec3 T = normalize(vec3(model * vec4(xTangent, 0.0)));
vec3 B = normalize(vec3(model * vec4(yTangent, 0.0)));
vec3 N = normalize(vec3(model * vec4(faceNormal, 0.0)));

mat3 TBN = mat3(T,B,N);
```

where T,B, and N stand for tangent, bitangent, and normal vectors.

We pull our normal from the normal map like so, scaling and offsetting the texture value appropriately:

'vec3 normal = texture(texture2, TexCoord).rgb *2.0f - 1.0f;'

Then multiply the TBN matrix by the normal vector to get the normal, correctly rotated to match the rotation of the face of the model.

### Bonus Features
Additionally inside 'texturenormal.fs' we allow the user to toggle the brick normal map off or on, and choose between different textures to see how the mapping processes change with different assets.