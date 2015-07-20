Stephen Burchill
10058882

Code for Dynamic eye position and viewing direction and spheres/plane/triangle developed from tutorial slides of Erika Harrison
Code used for phong/reflection/shadows/attenuation from lecture slides of Mario Costa Sousa
Bonus for dynamic viewing completed.

QT gui provided to adjust view of world as well as image size and background colour.

Actual material properties were used in the ray tracer. These properties were taken from the lecture slides.
the bottom plane is plastic material coloured blue(the material was modified to be 100% opaque)
the back plane is silver material as it is near 50% reflective

the three triangles are chrome, brass, and green plastic as they are approximately 70%, 30% reflective and opaque respectively.

the four spheres are chrome, gold, copper, pewter(which was modified to be opaque) as they are approximately 80%, 40%, 10% reflective and opaque respectively

4 images submitted

image noAttenuation shows all implemented spheres, planes, triangles with phong and reflection and shadows and 3 light sources
image attenuation shows the attenuation feature, this is visible mostly from the specular reflections for the lights in both the gold and polished silver spheres as the lights further away are dimmed
image moveableCamera shows the rendered attenuation image from another view point that was changed dynamically
image moveableCamera2 shows the gui/program window showing the controls used to change the view dynamic

Compile the program:
qmake CPSC453A3.pro -o makefile
make
Then run with:
./CPSC453A3
