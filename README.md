#AdtTools

This project aims to provide a framework to easily creating tools manipulating Adt's.  
These tools are compatible and tested with 2.4.3 and 3.3.5 versions. This is not tested with other versions, though I think this will work for 1.12 too.  

The process works in 3 steps : 

- Opening and generating the adt model in memory. The adt data is stored inside meaninful variables usable by tools, as opposed to working with raw bytes.
- One tool does the work on memory adt model. This allows great simplicity when creating tools.
- Adt model is recompiled into an adt file.

Some example tools are already done: 
- AllWaterPreWotLK  
  _Fill adt with MCLQ (< LK water) water at specified level._
- CopyPreWotLKWater  
  _Copy MCLQ (< LK water) from an adt to another._
- FixCamera  
  _Fix the annoying camera bug induced in Noggit where your character camera stay high in the sky._

This project is still a WIP, most adt chunks are still only partially interpreted and are stored as bytes streams. This means the data in these non interpreted chunks is kept as is and the interpretation system must be extended to allow simple usage.

There is also some work on a basic Qt interface for tools, you should ignore it for now. 

You can contact me at dr.kelno <at> gmail <dot> com if you're interested in using it, I may want to fix things for you.
