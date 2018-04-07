Renny

To update offsets:
Simply generate with Reclass (Make sure the header includes the Vector struct)
Then in the object class add a dereference (\*) before the member name mSpellDataInstArray
After, in the object class add a dereference (\*) before the member name mObjectManagerArray
Also ensure that the spellInst class has the following code in it's class in Reclass (open the class button and press code in the ribbon under home then under class)
