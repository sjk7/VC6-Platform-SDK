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
using System.Drawing;
using System.Collections;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Text;

using Microsoft.Uddi;
using Microsoft.Uddi.Businesses;
using Microsoft.Uddi.Extensions;
using Microsoft.Uddi.Services;
using Microsoft.Uddi.TModels;

using System.Diagnostics;

using UDDI.Tools;

namespace WsdlDiscovery
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class frmMain : System.Windows.Forms.Form
	{
		private System.Windows.Forms.Label _descriptionLabel;
		private System.Windows.Forms.Label _inquireLabel;
		private System.Windows.Forms.Label _extensionLabel;
		private System.Windows.Forms.Label _serviceLabel;
		private System.Windows.Forms.Label _providerLabel;
		private System.Windows.Forms.Label _categorizationLabel;
		private System.Windows.Forms.Label _resultsLabel;
		private System.Windows.Forms.GroupBox _groupBox1;
		private System.Windows.Forms.GroupBox _groupBox2;
		private System.Windows.Forms.GroupBox _groupBox3;
		private System.Windows.Forms.TextBox _inquireUrl;
		private System.Windows.Forms.TextBox _extensionUrl;
		private System.Windows.Forms.TextBox _serviceName;
		private System.Windows.Forms.TextBox _providerName;
		private System.Windows.Forms.Button _searchService;
		private System.Windows.Forms.Button _searchProvider;
		private System.Windows.Forms.Button _searchCategorization;
		private UDDI.Tools.CategoryTreeView _categories;
		private System.Windows.Forms.RichTextBox _results;
		private System.Windows.Forms.Button _loadSchemes;

		private bool _okToReloadSchemes = true;

		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public frmMain()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// Add any constructor code after InitializeComponent call
			//
			_inquireUrl.TextChanged += new EventHandler(_inquireUrl_TextChanged);
			_extensionUrl.TextChanged += new EventHandler(_extensionUrl_TextChanged);
			_providerName.TextChanged += new EventHandler(_providerName_TextChanged);
			_serviceName.TextChanged += new EventHandler(_serviceName_TextChanged);

			_categories.AfterSelect += new TreeViewEventHandler(_categories_AfterSelect);

			_searchCategorization.Enabled = false;

			SetSearchProviderButtonState();
			SetSearchServiceButtonState();
			SetLoadSchemesButtonState();
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if (components != null) 
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this._descriptionLabel = new System.Windows.Forms.Label();
			this._inquireLabel = new System.Windows.Forms.Label();
			this._extensionLabel = new System.Windows.Forms.Label();
			this._serviceLabel = new System.Windows.Forms.Label();
			this._providerLabel = new System.Windows.Forms.Label();
			this._categorizationLabel = new System.Windows.Forms.Label();
			this._resultsLabel = new System.Windows.Forms.Label();
			this._groupBox1 = new System.Windows.Forms.GroupBox();
			this._groupBox2 = new System.Windows.Forms.GroupBox();
			this._groupBox3 = new System.Windows.Forms.GroupBox();
			this._inquireUrl = new System.Windows.Forms.TextBox();
			this._extensionUrl = new System.Windows.Forms.TextBox();
			this._serviceName = new System.Windows.Forms.TextBox();
			this._providerName = new System.Windows.Forms.TextBox();
			this._searchService = new System.Windows.Forms.Button();
			this._searchProvider = new System.Windows.Forms.Button();
			this._searchCategorization = new System.Windows.Forms.Button();
			this._categories = new UDDI.Tools.CategoryTreeView();
			this._results = new System.Windows.Forms.RichTextBox();
			this._loadSchemes = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// _descriptionLabel
			// 
			this._descriptionLabel.Location = new System.Drawing.Point(24, 16);
			this._descriptionLabel.Name = "_descriptionLabel";
			this._descriptionLabel.Size = new System.Drawing.Size(408, 32);
			this._descriptionLabel.TabIndex = 0;
			this._descriptionLabel.Text = "This application searches a UDDI site for entities with WSDL described services. " +
				" Search by name or browse through available categorization schemes.";
			// 
			// _inquireLabel
			// 
			this._inquireLabel.Location = new System.Drawing.Point(24, 72);
			this._inquireLabel.Name = "_inquireLabel";
			this._inquireLabel.Size = new System.Drawing.Size(88, 24);
			this._inquireLabel.TabIndex = 1;
			this._inquireLabel.Text = "Inquire URL:";
			// 
			// _extensionLabel
			// 
			this._extensionLabel.Location = new System.Drawing.Point(24, 104);
			this._extensionLabel.Name = "_extensionLabel";
			this._extensionLabel.Size = new System.Drawing.Size(88, 24);
			this._extensionLabel.TabIndex = 2;
			this._extensionLabel.Text = "Extension URL:";
			// 
			// _serviceLabel
			// 
			this._serviceLabel.Location = new System.Drawing.Point(24, 152);
			this._serviceLabel.Name = "_serviceLabel";
			this._serviceLabel.Size = new System.Drawing.Size(88, 24);
			this._serviceLabel.TabIndex = 3;
			this._serviceLabel.Text = "Service Name:";
			// 
			// _providerLabel
			// 
			this._providerLabel.Location = new System.Drawing.Point(24, 184);
			this._providerLabel.Name = "_providerLabel";
			this._providerLabel.Size = new System.Drawing.Size(88, 24);
			this._providerLabel.TabIndex = 4;
			this._providerLabel.Text = "Provider Name:";
			// 
			// _categorizationLabel
			// 
			this._categorizationLabel.Location = new System.Drawing.Point(24, 216);
			this._categorizationLabel.Name = "_categorizationLabel";
			this._categorizationLabel.Size = new System.Drawing.Size(88, 24);
			this._categorizationLabel.TabIndex = 5;
			this._categorizationLabel.Text = "Categorization:";
			// 
			// _resultsLabel
			// 
			this._resultsLabel.Location = new System.Drawing.Point(24, 432);
			this._resultsLabel.Name = "_resultsLabel";
			this._resultsLabel.Size = new System.Drawing.Size(88, 24);
			this._resultsLabel.TabIndex = 6;
			this._resultsLabel.Text = "Results:";
			// 
			// _groupBox1
			// 
			this._groupBox1.Location = new System.Drawing.Point(24, 52);
			this._groupBox1.Name = "_groupBox1";
			this._groupBox1.Size = new System.Drawing.Size(400, 2);
			this._groupBox1.TabIndex = 7;
			this._groupBox1.TabStop = false;
			// 
			// _groupBox2
			// 
			this._groupBox2.Location = new System.Drawing.Point(24, 136);
			this._groupBox2.Name = "_groupBox2";
			this._groupBox2.Size = new System.Drawing.Size(400, 2);
			this._groupBox2.TabIndex = 8;
			this._groupBox2.TabStop = false;
			// 
			// _groupBox3
			// 
			this._groupBox3.Location = new System.Drawing.Point(24, 420);
			this._groupBox3.Name = "_groupBox3";
			this._groupBox3.Size = new System.Drawing.Size(400, 2);
			this._groupBox3.TabIndex = 9;
			this._groupBox3.TabStop = false;
			// 
			// _inquireUrl
			// 
			this._inquireUrl.Location = new System.Drawing.Point(112, 72);
			this._inquireUrl.Name = "_inquireUrl";
			this._inquireUrl.Size = new System.Drawing.Size(312, 20);
			this._inquireUrl.TabIndex = 6;
			this._inquireUrl.Text = "http://uddi.microsoft.com/inquire";
			// 
			// _extensionUrl
			// 
			this._extensionUrl.Location = new System.Drawing.Point(112, 104);
			this._extensionUrl.Name = "_extensionUrl";
			this._extensionUrl.Size = new System.Drawing.Size(312, 20);
			this._extensionUrl.TabIndex = 7;
			this._extensionUrl.Text = "http://uddi.microsoft.com/extension.asmx";
			// 
			// _serviceName
			// 
			this._serviceName.Location = new System.Drawing.Point(112, 152);
			this._serviceName.Name = "_serviceName";
			this._serviceName.Size = new System.Drawing.Size(248, 20);
			this._serviceName.TabIndex = 0;
			this._serviceName.Text = "";
			// 
			// _providerName
			// 
			this._providerName.Location = new System.Drawing.Point(112, 184);
			this._providerName.Name = "_providerName";
			this._providerName.Size = new System.Drawing.Size(248, 20);
			this._providerName.TabIndex = 2;
			this._providerName.Text = "";
			// 
			// _searchService
			// 
			this._searchService.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this._searchService.Location = new System.Drawing.Point(368, 152);
			this._searchService.Name = "_searchService";
			this._searchService.Size = new System.Drawing.Size(56, 24);
			this._searchService.TabIndex = 1;
			this._searchService.Text = "&Search";
			this._searchService.Click += new System.EventHandler(this._searchService_Click);
			// 
			// _searchProvider
			// 
			this._searchProvider.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this._searchProvider.Location = new System.Drawing.Point(368, 184);
			this._searchProvider.Name = "_searchProvider";
			this._searchProvider.Size = new System.Drawing.Size(56, 24);
			this._searchProvider.TabIndex = 3;
			this._searchProvider.Text = "S&earch";
			this._searchProvider.Click += new System.EventHandler(this._searchProvider_Click);
			// 
			// _searchCategorization
			// 
			this._searchCategorization.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this._searchCategorization.Location = new System.Drawing.Point(368, 384);
			this._searchCategorization.Name = "_searchCategorization";
			this._searchCategorization.Size = new System.Drawing.Size(56, 24);
			this._searchCategorization.TabIndex = 5;
			this._searchCategorization.Text = "Se&arch";
			this._searchCategorization.Click += new System.EventHandler(this._searchCategorization_Click);
			// 
			// _categories
			// 
			this._categories.Connection = null;
			this._categories.ImageIndex = -1;
			this._categories.Location = new System.Drawing.Point(112, 216);
			this._categories.Name = "_categories";
			this._categories.SelectedImageIndex = -1;
			this._categories.Size = new System.Drawing.Size(312, 160);
			this._categories.TabIndex = 17;
			// 
			// _results
			// 
			this._results.DetectUrls = false;
			this._results.Location = new System.Drawing.Point(24, 456);
			this._results.Name = "_results";
			this._results.ReadOnly = true;
			this._results.Size = new System.Drawing.Size(400, 184);
			this._results.TabIndex = 18;
			this._results.Text = "";
			this._results.WordWrap = false;
			// 
			// _loadSchemes
			// 
			this._loadSchemes.FlatStyle = System.Windows.Forms.FlatStyle.System;
			this._loadSchemes.Location = new System.Drawing.Point(264, 384);
			this._loadSchemes.Name = "_loadSchemes";
			this._loadSchemes.Size = new System.Drawing.Size(96, 24);
			this._loadSchemes.TabIndex = 4;
			this._loadSchemes.Text = "&Load schemes";
			this._loadSchemes.Click += new System.EventHandler(this._loadSchemes_Click);
			// 
			// frmMain
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(448, 661);
			this.Controls.Add(this._groupBox1);
			this.Controls.Add(this._loadSchemes);
			this.Controls.Add(this._results);
			this.Controls.Add(this._categories);
			this.Controls.Add(this._searchCategorization);
			this.Controls.Add(this._searchProvider);
			this.Controls.Add(this._searchService);
			this.Controls.Add(this._providerName);
			this.Controls.Add(this._serviceName);
			this.Controls.Add(this._extensionUrl);
			this.Controls.Add(this._inquireUrl);
			this.Controls.Add(this._groupBox3);
			this.Controls.Add(this._groupBox2);
			this.Controls.Add(this._resultsLabel);
			this.Controls.Add(this._categorizationLabel);
			this.Controls.Add(this._providerLabel);
			this.Controls.Add(this._serviceLabel);
			this.Controls.Add(this._extensionLabel);
			this.Controls.Add(this._inquireLabel);
			this.Controls.Add(this._descriptionLabel);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "frmMain";
			this.Text = "Find WSDL Services";
			this.ResumeLayout(false);

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			System.Windows.Forms.Application.EnableVisualStyles();
			Application.Run(new frmMain());
		}

		//
		// The text in the Inquire Url textbox has changed.  This might
		// affect wether some of the buttons should be enabled or not.
		//
		private void _inquireUrl_TextChanged(object sender, EventArgs e)
		{
			SetSearchProviderButtonState();
			SetSearchServiceButtonState();
			SetLoadSchemesButtonState();
		}

		//
		// The text in the Extension Url textbox has changed.  This might
		// affect wether some of the buttons should be enabled or not.
		//
		private void _extensionUrl_TextChanged(object sender, EventArgs e)
		{
			_okToReloadSchemes = true;

			SetLoadSchemesButtonState();
		}

		//
		// To perform the required search, we need an Inquire Url, and
		// a provider name to search on.
		//
		private void SetSearchProviderButtonState()
		{
			_searchProvider.Enabled = ( ( 0 != _inquireUrl.Text.Length ) && ( 0 != _providerName.Text.Length ) );
		}

		//
		// To perform the required search, we need an Inquire Url, and
		// a service name to search on.
		//
		private void SetSearchServiceButtonState()
		{
			_searchService.Enabled = ( ( 0 != _inquireUrl.Text.Length ) && ( 0 != _serviceName.Text.Length ) );
		}

		//
		// We can reload the categorization schemes only if:
		//
		// 1.  Either the Inquire Url or Extension Url has changed since
		//     the last reload.
		// 2.  An Inquire Url exists.
		// 3.  An Extension Url exists.
		//
		private void SetLoadSchemesButtonState()
		{
			_loadSchemes.Enabled = _okToReloadSchemes && ( ( 0 != _inquireUrl.Text.Length ) && ( 0 != _extensionUrl.Text.Length ) );
		}

		//
		// If the user has changed the provider name, they might have
		// changed it to an empty string.  So we check for this.
		//
		private void _providerName_TextChanged(object sender, EventArgs e)
		{
			SetSearchProviderButtonState();
		}

		//
		// If the user has changed the service name, they might have
		// changed it to an empty string.  So we check for this.
		private void _serviceName_TextChanged(object sender, EventArgs e)
		{
			SetSearchServiceButtonState();
		}

		//
		// Helper function.  Does a case insensitive search inside coll
		// for str.
		//
		private bool ContainsInsensitive( string str, StringCollection coll )
		{
			bool found = false;
			foreach( string s in coll )
			{
				if( 0 == string.Compare( str, s, true ) )
				{
					found = true;
					break;
				}
			}

			return found;
		}

		//
		// Helper function.  Return true iff the tModel uniquely identified by
		// tModelKey is present in the tModels collection.
		//
		private bool ContainsInsensitive( string tModelKey, TModelCollection tModels )
		{
			bool found = false;
			foreach( TModel tm in tModels )
			{
				if( 0 == string.Compare( tModelKey, tm.TModelKey, true ) )
				{
					found = true;
					break;
				}
			}

			return found;
		}

		//
		// Helper function.  Return the tModel from tModels whose TModelKey matches
		// tModelKey.  Return null if nothing is found.
		//
		private TModel GetTModel( string tModelKey, TModelCollection tModels )
		{
			foreach( TModel tm in tModels )
			{
				if( 0 == string.Compare( tModelKey, tm.TModelKey, true ) )
				{
					return tm;
				}
			}

			return null;
		}

		private void FillResultsControl( BusinessEntityCollection businessEntities, StringCollection serviceKeys, TModelCollection wsdlTModels )
		{
			//
			// RTF control words & characters.
			//
			const string startRTF		= @"{\rtf1\ansi{\stylesheet\deftab200}";
			const string endRTF			= @"}";
			const string boldOn			= @"\b ";
			const string boldOff		= @"\b0 ";
			const string tab			= @"\tab ";
			const string newLine		= @"\par ";
			
			//
			// Labels for the sections in our RTF output
			//
			const string serviceName	= @"Service: ";
			const string serviceDesc	= @"Description: ";
			const string bindings		= @"Binding: ";
			const string accessPoint	= @"Access Point: ";
			const string description	= @"Description: ";
			const string interfaceDefs	= @"Interface Definitions: ";

			_results.Clear();

			StringBuilder sb = new StringBuilder();

			sb.Append( startRTF );

			foreach( BusinessEntity be in businessEntities )
			{
				bool foundWsdlSvc = false;
				foreach( BusinessService bs in be.BusinessServices )
				{
					if( ContainsInsensitive( bs.ServiceKey, serviceKeys ) )
					{
						foundWsdlSvc = true;
						break;
					}
				}

				//
				// This particular business entity has no services which
				// are categorized as consumable by wsdl.  So, move onto
				// the next business entity.
				//
				if( false == foundWsdlSvc )
				{
					continue;
				}

				//
				// Just pick the 1st name out of the name collection.  The right
				// thing to do is either to show all names, or to determine the
				// CultureInfo of the current thread & try to display a name from
				// that language (if it exists in the collection ).
				//
				if( 0 < be.Names.Count )
				{
					sb.Append( boldOn + be.Names[ 0 ].Text + boldOff + newLine );
				}

				//
				// Just pick the 1st description out of the description collection.
				// The right thing to do is either to show all descriptions, or to
				// determine the CultureInfo of the current thread & try to display
				// a description from that language (if it exists in the collection ).
				//
				if( 0 < be.Descriptions.Count )
				{
					sb.Append( tab + be.Descriptions[ 0 ].Text + newLine + newLine );
				}

				foreach( BusinessService bs in be.BusinessServices )
				{
					//
					// We cannot assume that every Service owned by this particular
					// Business has been categorized as WSDL described.
					//
					if( !ContainsInsensitive( bs.ServiceKey, serviceKeys ) )
					{
						continue;
					}

					//
					// Just pick the 1st name out of the name collection.
					// The right thing to do is either to show all names, or to
					// determine the CultureInfo of the current thread & try to display
					// a name from that language (if it exists in the collection ).
					//
					sb.Append( tab + boldOn + serviceName + boldOff );
					if( 0 < bs.Names.Count )
					{
						sb.Append( bs.Names[ 0 ].Text + newLine );
					}


					//
					// Just pick the 1st description out of the description collection.
					// The right thing to do is either to show all descriptions, or to
					// determine the CultureInfo of the current thread & try to display
					// a description from that language (if it exists in the collection ).
					//
					if( 0 != bs.Descriptions.Count )
					{
						sb.Append( tab + boldOn + serviceDesc + boldOff );
						sb.Append( bs.Descriptions[ 0 ].Text + newLine );
					}
					sb.Append( newLine );

					//
					// Only display the BindingTemplate's description if it contains a
					// TModelInstanceInfo who's TModelKey property refers to a TModel
					// which is categorized as WSDL.
					//
					foreach( BindingTemplate bt in bs.BindingTemplates )
					{
						bool seenBindingTemplate = false;

						foreach( TModelInstanceInfo tmii in bt.TModelInstanceInfos )
						{
							if( !ContainsInsensitive( tmii.TModelKey, wsdlTModels ) )
							{
								continue;
							}
							//
							// A BindingTemplate could very well contain n TModelInstanceInfos,
							// all of which refer to TModels which are categorized as WSDL.  However,
							// we only want to display the BindingTemplate information once.
							//
							if( false == seenBindingTemplate )
							{
								sb.Append( tab + tab + boldOn + bindings + boldOff + newLine );
								sb.Append( tab + tab + tab + boldOn + accessPoint + boldOff + bt.AccessPoint.Text + newLine );

								if( 0 < bt.Descriptions.Count )
								{
									sb.Append( tab + tab + tab + boldOn + description + boldOff );
									//
									// Just pick the 1st description out of the description collection.
									// The right thing to do is either to show all descriptions, or to
									// determine the CultureInfo of the current thread & try to display
									// a description from that language (if it exists in the collection ).
									//
									sb.Append( bt.Descriptions[ 0 ].Text + newLine );
								}

								seenBindingTemplate = true;
							}

							sb.Append( tab + tab + tab + boldOn + interfaceDefs + boldOff + newLine );
							TModel wsdlTModel = GetTModel( tmii.TModelKey, wsdlTModels );
							if( null != wsdlTModel )
							{
								sb.Append( tab + tab + tab + wsdlTModel.OverviewDoc.OverviewUrl + newLine );
							}
						}
					}

					sb.Append( newLine );
				}
			}

			sb.Append( endRTF );
			_results.Rtf = sb.ToString();
		}

		private void _loadSchemes_Click(object sender, System.EventArgs e)
		{
			//
			// We need both the Inquire Url and the Extension Url.
			//
			// The InquireUrl is issued a FindTModel message to get us
			// summary information about all TModels which are categorized
			// as categorizations.  This will give us all the top level
			// nodes in the tree control.
			//
			// The Extension Url is used to issue GetRelatedCategories
			// messages.  These are issued every time someone expands
			// a tree node.
			//
			if( 0 == _inquireUrl.Text.Length )
			{
				MessageBox.Show( "Please specify an Inquire URL.", "Inquire URL missing", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
				return;
			}

			if( 0 == _extensionUrl.Text.Length )
			{
				MessageBox.Show( "Please specify an Extension URL.", "Extension URL missing", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
				return;
			}

			try
			{
				//
				// Create a connection object, pass it to our tree control
				// and let the control populate itself.
				//
				Cursor.Current = Cursors.WaitCursor;

				UddiConnection conn = new UddiConnection();
				conn.InquireUrl = _inquireUrl.Text;
				conn.ExtensionsUrl = _extensionUrl.Text;
				_categories.Connection = conn;

				if( null != _categories.Nodes )
				{
					_categories.Nodes.Clear();
				}

				_categories.LoadTModels();

				//
				// We've just loaded the schemes (TModels which are categorized
				// as categorizations.  So disable this load functionality until
				// the user changes either the Inquire Url or the Publish Url.
				//
				_okToReloadSchemes = false;
				SetLoadSchemesButtonState();
			}
			catch( Exception exception )
			{
				Cursor.Current = Cursors.Default;
				MessageBox.Show( exception.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );

				if( null != _categories.Nodes )
				{
					_categories.Nodes.Clear();
				}
				
				return;
			}
		}

		//
		// The topmost nodes in the treeview do not represent categories.
		// Rather they represent schemes.  Schemes contain categories.
		//
		// So after the user has selected a tree node, inspect the node
		// they have selected.  If it is a scheme node, disable the Search
		// by categorization button.  Otherwise enable it.
		//
		private void _categories_AfterSelect(object sender, TreeViewEventArgs e)
		{
			CategoryTreeNode catNode = (CategoryTreeNode)e.Node;

			_searchCategorization.Enabled = ( ( false == catNode.IsSchemeNode ) && ( _extensionUrl.Text.Length >= 0 ) );
			if( catNode.IsSchemeNode )
			{
				_searchCategorization.Enabled = false;
			}
			else
			{
				_searchCategorization.Enabled = true;
			}
		}

		private void _searchCategorization_Click(object sender, System.EventArgs e)
		{
			//
			// Two sanity checks.  These should never fire because the Search button
			// for categorizations should always be disabled in either of these 2 cases
			// (no tree node selected, or the selected node is not a category), but they
			// are here just in case.
			//
			CategoryTreeNode category = (CategoryTreeNode)_categories.SelectedNode;
			if( null == category )
			{
				MessageBox.Show( "Please select a category!", "Category not selected", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
				return;
			}

			if( null == category.CategoryValue.KeyValue )
			{
				MessageBox.Show( "This node represents a scheme, not a category.", "Category not selected", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
				return;
			}

			_results.Clear();

			UddiConnection conn = new UddiConnection();
			conn.InquireUrl = _inquireUrl.Text;

			Cursor.Current = Cursors.WaitCursor;

			//
			// Find all Services that are categorized as whatever value the user selected
			// in the category taxonomy.
			//
			ServiceList sl = null;
			try
			{
				Cursor.Current = Cursors.WaitCursor;

				FindService fs = new FindService();
				fs.CategoryBag.Add( category.CategoryValue.TModelKey, category.CategoryValue.KeyValue, null );

				sl = fs.Send( conn );
			}
			catch( Exception exception )
			{
				Cursor.Current = Cursors.Default;
				MessageBox.Show( exception.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
				return;
			}

			if( 0 == sl.ServiceInfos.Count )
			{
				Cursor.Current = Cursors.Default;
				MessageBox.Show( "No services matching the categorization were found.", "No services found", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
				return;
			}

			if( true == sl.Truncated )
			{
				MessageBox.Show( "The list of services matching the specified categorization was truncated by the server.  Consider using a more specific name.", "Truncated Results", MessageBoxButtons.OK, MessageBoxIcon.Information );
			}

			//
			// Get the full service detail from the above services.  This is
			// necessary because we need to look inside each binding to see
			// which tmodels are implemented by each service.
			//
			GetServiceDetail gsd = new GetServiceDetail();
			foreach( ServiceInfo si in sl.ServiceInfos )
			{
				gsd.ServiceKeys.Add( si.ServiceKey );
			}

			ServiceDetail sd = gsd.Send( conn );


			//
			// get a list of all (unique) tmodel keys implemented by the
			// services returned above.
			//
			StringCollection allTModelKeys = new StringCollection();
			foreach( BusinessService bs in sd.BusinessServices )
			{
				foreach( BindingTemplate bt in bs.BindingTemplates )
				{
					foreach( TModelInstanceInfo tmii in bt.TModelInstanceInfos )
					{
						if( !ContainsInsensitive( tmii.TModelKey, allTModelKeys ) )
						{
							allTModelKeys.Add( tmii.TModelKey );
						}
					}
				}
			}

			//
			// get the detail on each of these tmodels, and determine which
			// tmodels represent wsdl interfaces.
			//
			if( 0 == allTModelKeys.Count )
			{
				Cursor.Current = Cursors.Default;
				MessageBox.Show( "Services matching the categorization were found, however none of them implement tModels.", "No tModels found", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
				return;
			}

			TModelDetail tmd = null;
			try
			{
				GetTModelDetail gtmd = new GetTModelDetail();
				foreach( string key in allTModelKeys )
				{
					gtmd.TModelKeys.Add( key );
				}

				tmd = gtmd.Send( conn );
			}
			catch( Exception exception )
			{
				Cursor.Current = Cursors.Default;
				MessageBox.Show( exception.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
				return;
			}

			TModelCollection wsdlTModels = new TModelCollection();
			foreach( TModel tm in tmd.TModels )
			{
				foreach( KeyedReference categorization in tm.CategoryBag )
				{
					if( 0 == string.Compare( CommonCanonical.UddiOrgTypes, categorization.TModelKey, true ) &&
						0 == string.Compare( @"wsdlSpec", categorization.KeyValue, false ) &&
						false == ContainsInsensitive( tm.TModelKey, wsdlTModels ) )
					{
						wsdlTModels.Add( tm );
					}
				}
			}

			//
			// Now go through all of our business services from the
			// getservicedetail call & determine which ones implement
			// one of these tmodels.
			//
			if( 0 == wsdlTModels.Count )
			{
				Cursor.Current = Cursors.Default;
				MessageBox.Show( "Services matching the categorization were found, however none of them are WSDL described.", "No services found", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
				return;
			}

			StringCollection serviceKeys = new StringCollection();
			StringCollection businessKeys = new StringCollection();

			foreach( BusinessService bs in sd.BusinessServices )
			{
				foreach( BindingTemplate bt in bs.BindingTemplates )
				{
					foreach( TModelInstanceInfo tmii in bt.TModelInstanceInfos )
					{
						//
						// If we have hit an implementation of one of these tModels,
						// and if we don't already have the servicekey keep track of it.
						//
						if( ContainsInsensitive( tmii.TModelKey, wsdlTModels ) &&
							!ContainsInsensitive( bs.ServiceKey, serviceKeys ) )
						{
							serviceKeys.Add( bs.ServiceKey );

							//
							// If we don't already have the business key, keep track of it.
							//
							if( !ContainsInsensitive( bs.BusinessKey, businessKeys ) )
							{
								businessKeys.Add( bs.BusinessKey );
							}
						}
					}
				}
			}

			if( 0 == businessKeys.Count )
			{
				MessageBox.Show( "Nothing was found.", "No businesses found", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
				return;
			}

			GetBusinessDetail gbd = new GetBusinessDetail();
			gbd.BusinessKeys = businessKeys;

			BusinessDetail bd = gbd.Send( conn );

			FillResultsControl( bd.BusinessEntities, serviceKeys, wsdlTModels );

			Cursor.Current = Cursors.Default;
		}

		private void _searchProvider_Click(object sender, System.EventArgs e)
		{
			//
			// Two sanity checks.  These should never fire because the Search
			// by provider button should always be disabled if either one of
			// these is true.
			//
			if( 0 == _providerName.Text.Length )
			{
				MessageBox.Show( "Please specify a provider!", "No provider specified", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
				return;
			}
            
			if( 0 == _inquireUrl.Text.Length )
			{
				MessageBox.Show( "Please specify an Inquire URL.", "Inquire URL missing", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
				return;
			}

			_results.Clear();

			UddiConnection conn = new UddiConnection();
			conn.InquireUrl = _inquireUrl.Text;

			Cursor.Current = Cursors.WaitCursor;

			//
			//  1.  Find all Businesses who's name matches what the user typed in.
			//
			BusinessList bl = null;
			try
			{
				FindBusiness fb = new FindBusiness();
				fb.Names.Add( _providerName.Text );
				bl = fb.Send( conn );
			}
			catch( Exception exception )
			{
				Cursor.Current = Cursors.Default;
				MessageBox.Show( exception.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
				return;
			}

			if( 0 == bl.BusinessInfos.Count )
			{
				Cursor.Current = Cursors.Default;
				MessageBox.Show( "No providers matching the specified name were found.", "No providers found", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
				return;
			}

			if( true == bl.Truncated )
			{
				MessageBox.Show( "The list of providers matching the specified name was truncated by the server.  Consider specifying a more restrictive name.", "Truncated Results", MessageBoxButtons.OK, MessageBoxIcon.Information );
			}

			//
			// 2.  Do a GetBusinessDetail on all the Businesses returned from #1.
			//     This will get us every bit of information about each Business,
			//     each Businesses BusinessService, and each BindingDetail owned
			//     by each BusinessService.
			//
			BusinessDetail bd = null;
			try
			{
				GetBusinessDetail gbd = new GetBusinessDetail();
				foreach( BusinessInfo bi in bl.BusinessInfos )
				{
					gbd.BusinessKeys.Add( bi.BusinessKey );
				}

				bd = gbd.Send( conn );
			}
			catch( Exception exception )
			{
				Cursor.Current = Cursors.Default;
				MessageBox.Show( exception.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
				return;
			}


			//
			// 3.  Get a list of all unique tmodel keys which are implemented
			//     by the services owned by the businesses retrieved above.
			//
			StringCollection allTModelKeys = new StringCollection();
			foreach( BusinessEntity be in bd.BusinessEntities )
			{
				foreach( BusinessService bs in be.BusinessServices )
				{
					foreach( BindingTemplate bt in bs.BindingTemplates )
					{
						foreach( TModelInstanceInfo tmii in bt.TModelInstanceInfos )
						{
							if( false == ContainsInsensitive( tmii.TModelKey, allTModelKeys ) )
							{
								allTModelKeys.Add( tmii.TModelKey );
							}
						}
					}
				}
			}

			//
			// 4.  Now determine which of these tmodels are categorized as
			//     wsdl interfaces.
			//
			if( 0 == allTModelKeys.Count )
			{
				Cursor.Current = Cursors.Default;
				MessageBox.Show( "Businesses matching the specified name were found, but none implement a tModel.", "No tModels found", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
				return;
			}

			TModelDetail tmd = null;
			try
			{
				GetTModelDetail gtmd = new GetTModelDetail();
				foreach( string key in allTModelKeys )
				{
					gtmd.TModelKeys.Add( key );
				}

				tmd = gtmd.Send( conn );
			}
			catch( Exception exception )
			{
				Cursor.Current = Cursors.Default;
				MessageBox.Show( exception.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
				return;
			}

			TModelCollection wsdlTModels = new TModelCollection();

			foreach( TModel tm in tmd.TModels )
			{
				foreach( KeyedReference categorization in tm.CategoryBag )
				{
					if( 0 == string.Compare( CommonCanonical.UddiOrgTypes, categorization.TModelKey, true ) &&
						0 == string.Compare( @"wsdlSpec", categorization.KeyValue, false ) &&
						false == ContainsInsensitive( tm.TModelKey, wsdlTModels ) )
					{
						wsdlTModels.Add( tm );
					}
				}
			}

			//
			// 5.  now we have a list of businesses named what we want.
			//     we also have a list of tmodel keys which we know represent
			//     tmodels which are categorized as wsdl interfaces.
			//     we will now get a list of service keys representing
			//     services owned by these businesses which implement these
			//     tmodels.
			//
			if( 0 == wsdlTModels.Count )
			{
				Cursor.Current = Cursors.Default;
				MessageBox.Show( "Businesses matching the specified name were found, but none have services described with WSDL.", "No tModels found", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
				return;
			}

			StringCollection serviceKeys = new StringCollection();
			foreach( BusinessEntity be in bd.BusinessEntities )
			{
				foreach( BusinessService bs in be.BusinessServices )
				{
					foreach( BindingTemplate bt in bs.BindingTemplates )
					{
						foreach( TModelInstanceInfo tmii in bt.TModelInstanceInfos )
						{
							if( ContainsInsensitive( tmii.TModelKey, wsdlTModels ) &&
								!ContainsInsensitive( bs.ServiceKey, serviceKeys ) )
							{
								serviceKeys.Add( bs.ServiceKey );
							}
						}
					}
				}
			}

			FillResultsControl( bd.BusinessEntities, serviceKeys, wsdlTModels );

			Cursor.Current = Cursors.Default;
		}

		private void _searchService_Click(object sender, System.EventArgs e)
		{
			//
			// Two sanity checks.  These should never fire because the Search by
			// service button should always be disabled in either of these cases.
			//
			if( 0 == _serviceName.Text.Length )
			{
				MessageBox.Show( "Please specify a service name", "Service name missing", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
				return;
			}
            
			if( 0 == _inquireUrl.Text.Length )
			{
				MessageBox.Show( "Please specify an Inquire URL.", "Inquire URL missing", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
				return;
			}

			_results.Clear();

			UddiConnection conn = new UddiConnection();
			conn.InquireUrl = _inquireUrl.Text;

			Cursor.Current = Cursors.WaitCursor;

			//
			// Find all services that match the specified name.
			//
			ServiceList sl = null;
			try
			{
				FindService fs = new FindService();
				fs.Names.Add( _serviceName.Text );
				sl = fs.Send( conn );
			}
			catch( Exception exception )
			{
				Cursor.Current = Cursors.Default;
				MessageBox.Show( exception.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
				return;
			}

			if( 0 == sl.ServiceInfos.Count )
			{
				Cursor.Current = Cursors.Default;
				MessageBox.Show( "No services matching the specified name were found.", "No services found", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
				return;
			}

			if( true == sl.Truncated )
			{
				MessageBox.Show( "The list of services matching the specified name was truncated by the server.  Consider using a more specific name.", "Truncated Results", MessageBoxButtons.OK, MessageBoxIcon.Information );
			}

			//
			// get the full service detail from the above services.  this is
			// necessary because we need to look inside each binding to see
			// which tmodels are implemented by each service.
			//
			GetServiceDetail gsd = new GetServiceDetail();
			foreach( ServiceInfo si in sl.ServiceInfos )
			{
				gsd.ServiceKeys.Add( si.ServiceKey );
			}

			ServiceDetail sd = null;
			try
			{
				sd = gsd.Send( conn );
			}
			catch( Exception exception )
			{
				Cursor.Current = Cursors.Default;
				MessageBox.Show( exception.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
				return;
			}

			//
			// get a list of all (unique) tmodel keys implemented by the
			// services returned above.
			//
			StringCollection allTModelKeys = new StringCollection();
			foreach( BusinessService bs in sd.BusinessServices )
			{
				foreach( BindingTemplate bt in bs.BindingTemplates )
				{
					foreach( TModelInstanceInfo tmii in bt.TModelInstanceInfos )
					{
						if( !ContainsInsensitive( tmii.TModelKey, allTModelKeys ) )
						{
							allTModelKeys.Add( tmii.TModelKey );
						}
					}
				}
			}

			//
			// get the detail on each of these tmodels, and determine which
			// tmodels represent wsdl interfaces.
			//
			if( 0 == allTModelKeys.Count )
			{
				Cursor.Current = Cursors.Default;
				MessageBox.Show( "Services matching the specified name were found, however none implement tModels.", "No tModels found", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
				return;
			}

			TModelDetail tmd = null;
			try
			{
				GetTModelDetail gtmd = new GetTModelDetail();
				foreach( string key in allTModelKeys )
				{
					gtmd.TModelKeys.Add( key );
				}

				tmd = gtmd.Send( conn );
			}
			catch( Exception exception )
			{
				Cursor.Current = Cursors.Default;
				MessageBox.Show( exception.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
				return;
			}

			TModelCollection wsdlTModels = new TModelCollection();
			foreach( TModel tm in tmd.TModels )
			{
				foreach( KeyedReference categorization in tm.CategoryBag )
				{
					if( 0 == string.Compare( CommonCanonical.UddiOrgTypes, categorization.TModelKey, true ) &&
						0 == string.Compare( @"wsdlSpec", categorization.KeyValue, false ) &&
						false == ContainsInsensitive( tm.TModelKey, wsdlTModels ) )
					{
						wsdlTModels.Add( tm );
					}
				}
			}

			//
			// now go through all of our business services from the
			// getservicedetail call & determine which ones implement
			// one of these tmodels.
			//
			if( 0 == wsdlTModels.Count )
			{
				Cursor.Current = Cursors.Default;
				MessageBox.Show( "Services matching the specified name were found, however none are WSDL described.", "No tModels found", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
				return;
			}

			StringCollection serviceKeys = new StringCollection();
			StringCollection businessKeys = new StringCollection();

			foreach( BusinessService bs in sd.BusinessServices )
			{
				foreach( BindingTemplate bt in bs.BindingTemplates )
				{
					foreach( TModelInstanceInfo tmii in bt.TModelInstanceInfos )
					{
						if( ContainsInsensitive( tmii.TModelKey, wsdlTModels ) &&
							!ContainsInsensitive( bs.ServiceKey, serviceKeys ) )
						{
							serviceKeys.Add( bs.ServiceKey );

							if( !ContainsInsensitive( bs.BusinessKey, businessKeys ) )
							{
								businessKeys.Add( bs.BusinessKey );
							}
						}
					}
				}
			}

			if( 0 == businessKeys.Count )
			{
				MessageBox.Show( "Nothing was found.", "No businesses found", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
				return;
			}

			GetBusinessDetail gbd = new GetBusinessDetail();
			gbd.BusinessKeys = businessKeys;

			BusinessDetail bd = null;
			
			try
			{
				bd = gbd.Send( conn );
			}
			catch( Exception exception )
			{
				Cursor.Current = Cursors.Default;
				MessageBox.Show( exception.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation );
				return;
			}

			FillResultsControl( bd.BusinessEntities, serviceKeys, wsdlTModels );

			Cursor.Current = Cursors.Default;
		}
	}
}
