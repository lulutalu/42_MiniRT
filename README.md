# 42_MiniRT

## Summary

This project is an introduction to the beautiful world of Raytracing.<br>
Once completed we'll be able to render simple Computer-Generated-Images<br>
and the objective is to not be afraid of implementing mathematical formulas again.

## Todo

Implement a functionning RayTracing algorithm. <br>Take in account the eventuals optimizations : Fixed point number calculs, multi-threading, ...<br>

Have a reader for the instructions. The instructions will be passed in parameter inside a .rt file.<br>

Possible Instructions :<br>
Ambient Lightning : `A 0.2 255,255,255`<br>
Camera : `C -50.0,0,20 0,0,1 70`<br>
Light : `L -40.0,50.0,0.0 0.6 10,0,255`<br>

Sphere : `sp 0.0,0.0,20.6 12.6 10,0,255`<br>
Plane : `pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225`<br>
Cylinder : `cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255`<br>

There's at least three kind of geometry to display :<br>
`Planes`<br>
`Spheres`<br>
`Cylinders`<br>

The programm should be able to resize those geometries<br>
`Diameter` for Spheres<br>
`Width and Height` for Cylinders<br>

Movement of the Objects should also be implemented<br>
`Translation` for Objects, Light and Camera<br>
`Rotation` for Objects (excluding Spheres) and Camera as Lights can't be rotated<br>

Few things for Light management :<br>
`Ambient Lightning`<br>
`Diffuse Lightning`<br>
Also, Objects should never be in the complete Dark.

## Sources

https://web.cse.ohio-state.edu/~shen.94/681/Site/Slides_files/basic_algo.pdf<br>
https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-ray-tracing/how-does-it-work<br>
https://www.realtimerendering.com/raytracing/Ray%20Tracing%20in%20a%20Weekend.pdf<br>
https://gabrielgambetta.com/computer-graphics-from-scratch/02-basic-raytracing.html<br>
