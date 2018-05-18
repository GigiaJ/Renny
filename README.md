Renny

To update offsets:
Simply generate with Reclass (Make sure the header includes the Vector struct)

Will be adding a script to generate most offsets from within IDA Pro

To update addresses:
Run the signature scanner in IDA on the latest patch.
Ensure no signatures returned an error.
Paste in the updated signatures.
If an error does return, most likely I've documented the method to find the address on any patch.
