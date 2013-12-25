Evergreen
=========

A blinky replacement for homemade cookies. This funky sparkly christmas tree features a completely reprogramable ATtiny85.
Also, large pads allow to strap it to some other contraption. The imagination is the limit!

Bill of Material
----------------

* ATtiny85 (SOIC8),
* 5x SMD LED (0805),
* 5x corresponding resistors (0805),
* 1x tiny [slide switch](http://www.mouser.com/Search/ProductDetail.aspx?R=SSAJ120100virtualkey68800000virtualkey688-SSAJ120100),
* and a CR 2032 coin cell holder such as [this one](http://www.mouser.com/Search/ProductDetail.aspx?R=3034virtualkey53400000virtualkey534-3034).

Voltage considerations
----------------------

The board runs directly from the battery voltage (3V or less), so the LED voltage drop should be 2.5V or less.

Printing and cutting
--------------------

Mask files are provided to print eight boards at a time. Alignment points are also provided. After printing the mask, the printed side (with the ink) should go
directly against the copper (hence the top mask is mirrored).

The alignment marks on the cut outline correspond to the alignment mark of the mask. This is to allow CNC cutting of the boards.

To print less boards, it is enough to delete the extra boards in the files.

License
-------

Beerware ;)
