/////////////////////////////////////////////////////////////////////////////
MMC SDK Sample Project:  DragDrop

Summary:
- This project requires MMC 2.0  
- This project implements interprocess Drag & Drop.


/////////////////////////////////////////////////////////////////////////////
//  Implementing Drag & Drop in MMC 2.0


* Verbs: Implement MMC_VERB_CUT/COPY/PASTE for each node class.

* Add a new clipboard format to return a NODE_PROPERTIES struct.

* Add a new clipboard format to return a Node Type flag
 
* Add support for IDataObject::QueryGetData.  QueryGetData should support
  the new custom clipboard formats we need for DragDrop.
 
* Add support for IDataObject::GetData.  This method will support the new
  DragDrop custom clipboard formats
 
* Add support for IDataObject::EnumFormatEtc.  This method enumerates the
  custom clipboard formats we use for interprocess DragDrop

* Handle the MMCN_QUERY_PASTE notification.  In MMC20 this has a new parameter
  which allows us to tell the console if we want the default behaviour to be
  copy or move. 

* Handle the MMCN_PASTE notification. 

* Handle the MMCN_CUTORMOVE notification.

* Handle the MMCN_CANPASTE_OUTOFPROC notification


/////////////////////////////////////////////////////////////////////////////
// DragDrop behaviour for differenet node types


* CStaticNode:  Cannot be copied, moved or accept objects to be pasted.

* CDeviceNode:  Cannot be copied or moved.  It can be a target for CFolderNode
                objects.  The default operation is "Copy Here" 
                
* CFolderNode:  Can be copied or moved.  Since FolderNodes can have child
                nodes, Copy/Move operations include all child items.  This
                node can also be a paste target for CVirtualFile nodes.  The
                default operation for this node type is "Move Here" 
                              
* CVirtualFile: Can be copied or moved.  The targets allowed are CFolderNode.
                CFolderNode and CVirtualFile.  In the case of a copy/move to 
                another CVirtualFile only the properties are copied.  The 
                default operation is "Copy Here".  A check is made to make 
                sure a node is not copied or moved to itself.


