'------------------------------------------------------
' Active Directory Other Well know container
'
'---------------------------------------------------------------------

This program does the following:
1. Creates a container (MyWKOTestContainer) in the current Window 2000 domain.
2. Creates a container object (MyWKOTestObject) within the container.
3. Adds a value for the container object on the otherWellKnownObject property of the container.
4. Binds to the container object using WKGUID binding string.
5. Renames the container object using WKGUID binding string.
6. Binds to the container object using WKGUID binding string.
7. Optionally, cleans up by removing the container and container object.
