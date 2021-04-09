/*Write a graphics application that shows a building on Coe’s campus in three levels of detail (LOD).
The building must have at least one feature that is curved, such as a wall, arched windows, columns or steeple. 

At the crudest LOD, used when the viewer is far from the building, the curved feature may only have a few segments and other architectural 
features may be left out or approximated. 

At the finest LOD, used when the viewer is close, the curve feature should be very smooth and all
other architectural features shown in full form. The middle LOD should be about halfway between the other two.  
Under the viewing system described below, the LOD should switch automatically based on how far the viewer is from the building (e.g., when zooming in or out). 

You can create your models by hand, or use a tool of your choosing. 
In either case, you will need to provide surface normals and assign them to vertices in order to correctly shade the curved 
feature and the other parts of the building. Assign material properties as appropriate to different parts of the building. 
Make sure to “ground” your building by providing the surrounding 50 – 100 feet of sidewalk and lawn (and trees if you are really ambitious). 

Add global ambient light, two or more positional lights that will distinctly light the model (e.g., light primarily shown on different parts of the building), 
and, optionally, a directional light (e.g., the sun). Global ambient light, when turned on, should have a low intensity, but should be bright enough to see the building clearly.  
The lights must remain stationary.  Note:  Modeling transformations affect lights, so be careful.  
*/