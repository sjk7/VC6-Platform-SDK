/*=====================================================================
  This file is part of the Microsoft UDDI SDK Code Samples.

  Copyright (C) Microsoft Corporation.  All rights reserved.

This source code is intended only as a supplement to Microsoft
Development Tools and/or on-line documentation.  See these other
materials for detailed information regarding Microsoft code samples.

THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.
=====================================================================*/

using System;
using System.Collections;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Windows.Forms;

using Microsoft.Uddi;
using Microsoft.Uddi.TModels;
using Microsoft.Uddi.Extensions;

namespace UDDI.Tools
{
	/// <summary>
	/// Summary description for categorytree.
	/// </summary>
	public class CategoryTreeView : TreeView
	{
		/// <summary> 
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;
		private UddiConnection _connection;

		public CategoryTreeView(  )
		{
			// This call is required by the Windows.Forms Form Designer.
			InitializeComponent();
	
		}

		public CategoryTreeView( UddiConnection connection ) : this()
		{
			_connection = connection;
		}

		public UddiConnection Connection
		{
			get{ return _connection; }
			set{ _connection = (UddiConnection)value; }
		}


		/// <summary> 
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if(components != null)
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		

		public void LoadTModels( )
		{
			FindTModel ft = new FindTModel();
			ft.CategoryBag.Add( CommonCanonical.UddiOrgTypes, "categorization", "Categorization (taxonomy)" );

			TModelList list = null;
			try
			{
				list = ft.Send( _connection );
			}
			catch( Exception e )
			{
				MessageBox.Show( this, e.Message, @"Error loading Category Tree", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
				return;
			}
			
			if( null == list )
			{
				MessageBox.Show( this, @"An unknown error occurred while loading the Category Tree.", @"Error loading Category Tree", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
				return;
			}

			GetRelatedCategories grc = new GetRelatedCategories();
			Category c = new Category();
			c.RelationshipQualifiers.Add( RelationshipQualifier.root );

			foreach( TModelInfo info in list.TModelInfos )
			{
				bool categorization = false;
				c.TModelKey = info.TModelKey;
				grc.Categories.Add( c );

				CategoryList cl = null;
				try
				{
					cl = grc.Send( _connection );
					categorization = true;
				}
				catch( InvalidKeyPassedException )
				{
					//
					// tModel doesn't represent a categorization.  So, don't show
					// it in the tree.
					//
				}
				catch( Exception e )
				{
					//
					// if anything else happened, re-throw & let the app deal with it.
					//
					throw e;
				}

				if( categorization )
				{
					//
					// Create a new node and wrap the tModelInfo into a 
					// CategoryInfo object.
					//
					CategoryTreeNode catnode = new CategoryTreeNode( new CategoryInfo( info.TModelKey ) );
				
					catnode.Nodes.Clear();

					//
					// Set the Text of the node to the text of the tModel.
					//
					catnode.Text =  info.Name.Text;
				
					CategoryValueCollection values = cl.CategoryInfos[ 0 ].Roots;

					foreach( CategoryValue val in values )
					{
						CategoryTreeNode subnode = new CategoryTreeNode( val );
						subnode.CategoryValue.TModelKey = catnode.CategoryValue.TModelKey;
						catnode.Nodes.Add( subnode );
					}

					catnode.HasDownloadedChildren = true;

					//
					// Add the node to the root.
					//
					Nodes.Add( catnode );
				}
			}
		}


		private void GetChildren( CategoryTreeNode node )
		{
			node.Nodes.Clear();

			GetRelatedCategories grc = new GetRelatedCategories();
			
			Category cat = new Category( node.CategoryValue.TModelKey, node.CategoryValue.KeyValue );
			grc.Categories.Add( cat );
			
			
			//
			// If the Parent is null, it is a root node (tModel)
			//
			if( node.IsSchemeNode )
				grc.Categories[ 0 ].RelationshipQualifiers.Add( RelationshipQualifier.root );
			else
				grc.Categories[ 0 ].RelationshipQualifiers.Add( RelationshipQualifier.child );
			
			CategoryList list = null;
			try
			{
				list = grc.Send( _connection );
			}
			catch( Exception e )
			{
				MessageBox.Show( this, e.Message, "Error Loading Tree Node" );
				return;
			}

			
			CategoryValueCollection values;
			
			if( node.IsSchemeNode )
				values = list.CategoryInfos[ 0 ].Roots;
			else 
				values = list.CategoryInfos[ 0 ].Children;

			foreach( CategoryValue val in values )
			{
				CategoryTreeNode subnode = new CategoryTreeNode( val );
				subnode.CategoryValue.TModelKey = node.CategoryValue.TModelKey;
				node.Nodes.Add( subnode );
			}

			node.HasDownloadedChildren = true;
			
		
		}

		#region Component Designer generated code
		/// <summary> 
		/// Required method for Designer support - do not modify 
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			// 
			// CategoryTree
			// 
			this.BeforeExpand += new System.Windows.Forms.TreeViewCancelEventHandler(this.CategoryTree_BeforeExpand);

		}
		#endregion

		private void CategoryTree_BeforeExpand(object sender, System.Windows.Forms.TreeViewCancelEventArgs e)
		{
			CategoryTreeNode node = (CategoryTreeNode)e.Node;
			if( !node.HasDownloadedChildren )
			{
				GetChildren( node );
			}
		}
	}

	public class CategoryTreeNode : TreeNode
	{
		private CategoryTreeNode(){}
		public CategoryTreeNode( CategoryValue val )
		{
			_categoryValue = val;
			
			Text = val.KeyName;
			//
			// Add a blank node to force the + sign.
			//
			Nodes.Add( new TreeNode() );
		}

		private CategoryValue _categoryValue;
		private bool _hasDownloadedChildren;

		public CategoryValue CategoryValue
		{
			get{ return _categoryValue; }
		}
		internal bool IsSchemeNode
		{
			get{ return null == Parent; }
		}
		internal bool HasDownloadedChildren
		{
			get{ return _hasDownloadedChildren; }
			set{ _hasDownloadedChildren = value; }
		}
	}
}
