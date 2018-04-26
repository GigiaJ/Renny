Renny

To update offsets:
Simply generate with Reclass (Make sure the header includes the Vector struct)
Typedef should be 
int16 = int
int8 = bool
Vec3 = Vector
Also ensure that the spellInst, spellCastDataBase, and object all have the appropriate code code in their classes in Reclass (open the class button and press code in the ribbon under home then under class)
Offsets can be wrong depending on patch so that is something to be aware of.

To update addresses:
Run the signature scanner in IDA on the latest patch.
Ensure no signatures returned an error.
Paste in the updated signatures.
If an error does return, most likely I've documented the method to find the address on any patch.
