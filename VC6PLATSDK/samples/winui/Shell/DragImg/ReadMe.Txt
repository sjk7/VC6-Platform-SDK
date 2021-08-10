Drag Image Helper Sample DragImg

The DragImg sample demonstrates how to use the Drag Image Helper object to display enhanced and shared OLE drag and drop images. 

The Drag Image Helper object allows applications and components to display enhanced OLE drag and drop images while acting either as the source or the target of an OLE drag and drop operation. This capability is available in Windows 2000. The Drag Image Helper actually consists of two separate objects, the Drag Source Helper and the Drop Target Helper.

The Drag Source Helper object allows an application or component to display enhanced drag and drop images in the same way that Explorer does. These same images will be displayed while dragging over an Explorer window (such as the Desktop) or any other window that utilizes the Drop Target Helper object.

The Drop Target Helper allows an application to display enhanced drag and drop images while the user is dragging objects over the drop target. The drag images must be implemented by the Drag Source Helper for them to be displayed by the Drop Target Helper. This includes all Explorer windows (such as the Desktop) and any other drag source that utilizes the Drag Source Helper.
