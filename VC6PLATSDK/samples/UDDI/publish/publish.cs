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
using Microsoft.Uddi;
using Microsoft.Uddi.Businesses;
using Microsoft.Uddi.Extensions;
using Microsoft.Uddi.Services;
using Microsoft.Uddi.TModels;

namespace Microsoft.Uddi.Demo
{
	public class Publish
	{
		static UddiConnection _connection;

		/// <summary>
		///		Entry Point
		/// </summary>
		public static void Main( )
		{
			
			//
			// Attempt to find the first site listed in Active Directory
			//
			UddiSiteLocation location = GetFirstLocation( AuthenticationMode.WindowsAuthentication );
			
			//
			// Create a location if no location was returned from Active Directory
			// These settings use the default access points for UDDI Services and Windows Authentication
			// TODO: Update with actual servername
			//

			string httpServerName = "http://servername/uddi/";
			string httpsServerName = "https://servername/uddi/";
			
			if( null == location )
			{
				location = new UddiSiteLocation( 
					httpServerName + "inquire.asmx",
					httpsServerName + "publish.asmx",
					httpServerName + "extension.asmx",
					"My Site",
					AuthenticationMode.WindowsAuthentication );
			}

			//
			// Create the connection object.
			//
			_connection = new UddiConnection( location );
		

			Console.WriteLine( "Current Data" );
			
			//
			// Display the current entities owned by this publisher
			//
			DisplayOwnedEntities();
			
			Console.WriteLine( "Saving New Data" );
			
			//
			// Create a new Provider.
			//
			BusinessEntity entity = SaveNewProvider( "My New Provider Name", "Description of my new Provider" );
			
			//
			// Add a new Service to that provider
			//
			AddService( entity, "My New Service", "Description for my new Service" );

			Console.WriteLine( "New Data" );

			//
			// Display the currently owned entities again.
			//
			DisplayOwnedEntities();
			
			Console.WriteLine( "Taxonomy Data" );
			
			//
			// Display the taxonomy information for UddiOrgTypes.
			//
			DisplayTaxonomy( CommonCanonical.UddiOrgTypes );
		}

		/// <summary>
		///		Searches Active Directory for Uddi Sites, using the specified Authentication
		///		Mode as criteria for the search.
		/// </summary>
		/// <param name="mode"> The authentication mode you would like to query for.</param>
		/// <returns>The first UddiSiteLocation registered with Active Directory.</returns>
		private static UddiSiteLocation GetFirstLocation( AuthenticationMode mode )
		{
			UddiSiteLocation[] locations = UddiSiteDiscovery.Find( UddiSiteUrlType.All, mode );
			if( locations.Length > 0 )
				return locations[ 0 ];
			else
				return null;

		}

		/// <summary>
		///		Writes information about the current publishers owned data to STDOUT
		/// </summary>
		private static void DisplayOwnedEntities()
		{
			GetRegisteredInfo gri = new GetRegisteredInfo();
			RegisteredInfo ri = gri.Send( _connection );

			foreach( BusinessInfo binfo in ri.BusinessInfos )
			{
				Console.WriteLine( "Business Entity" );
				Console.WriteLine( "\tName: " + binfo.Names[ 0 ].Text );
				Console.WriteLine( "\tBusinessKey: " + binfo.BusinessKey );
				Console.WriteLine( "\tServiceCount: " + binfo.ServiceInfos.Count );
			}
			foreach( TModelInfo tinfo in ri.TModelInfos )
			{
				Console.WriteLine( "Business Entity" );
				Console.WriteLine( "\tName: " + tinfo.Name.Text );
				Console.WriteLine( "\tTModelKey: " + tinfo.TModelKey );
			}

		}

		/// <summary>
		///		Saves a new BusinessEntity object with the specified name and 
		///		description.
		/// </summary>
		/// <param name="name">Name for the new BusinessEntity.</param>
		/// <param name="desc">Description for the new BusinessEntity.</param>
		/// <returns>The Resulting BusinessEntity after saving it.</returns>
		private static BusinessEntity SaveNewProvider( string name, string desc )
		{
			BusinessEntity entity = new BusinessEntity();
			entity.Names.Add( name );
			entity.Descriptions.Add( desc );
			
			SaveBusiness sb = new SaveBusiness( entity );
			BusinessDetail detail = sb.Send( _connection );
			
			return detail.BusinessEntities[ 0 ];
		}

		/// <summary>
		///		Create a service, and save it using the provided BusinessEntity, name, and
		///		description.
		/// </summary>
		/// <param name="entity">The BusinessEntity that will own this BusinessService.</param>
		/// <param name="name">The name for the new BusinessService.</param>
		/// <param name="desc">The description for the new BusinessService.</param>
		/// <returns>The resulting BusinessService after the save.</returns>
		private static BusinessService AddService( BusinessEntity entity, string name, string desc )
		{
			BusinessService service = new BusinessService();
			service.BusinessKey = entity.BusinessKey;
			service.Names.Add( name );
			service.Descriptions.Add( desc );

			SaveService ss = new SaveService( service );
			ServiceDetail detail = ss.Send( _connection );

			return detail.BusinessServices[ 0 ];
		}
		
		/// <summary>
		///		Displays the Taxonomy information for a specified TModelKey.
		/// </summary>
		/// <param name="key">TModelKey to perferm the Categorization lookup on.</param>
		private static void DisplayTaxonomy( string key )
		{
			Category cat = new Category( key );
			cat.RelationshipQualifiers.Add( RelationshipQualifier.root );

			GetRelatedCategories grc = new GetRelatedCategories();
			
			grc.Categories.Add( cat );

			CategoryList list = grc.Send( _connection );
			
			foreach( CategoryInfo info in list.CategoryInfos )
			{
				Console.WriteLine( info.TModelKey );
				foreach( CategoryValue cv in info.Roots )
				{
					Console.WriteLine( "\t" + cv.KeyName + "(" + cv.KeyValue + ")" );
					DisplayTaxonomyItems( info.TModelKey, cv.KeyValue, 2 );
				}
			}
		}

		/// <summary>
		///			Displays the Taxonomy information for a specified TModelKey, begining
		///			at a specified KeyValue.  
		/// </summary>
		/// <param name="key">TModelKey for the the Taxonomy</param>
		/// <param name="value">KeyValue to start from.</param>
		/// <param name="tabs">Number or \t characters to prepend to the Output.</param>
		private static void DisplayTaxonomyItems( string key, string value, int tabs )
		{
			string line = "";
			for( int i = 0;i<tabs;i++ )
				line += "\t";


			Category cat = new Category( key, value );
			cat.RelationshipQualifiers.Add( RelationshipQualifier.child );

			GetRelatedCategories grc = new GetRelatedCategories();
			
			grc.Categories.Add( cat );

			CategoryList list = grc.Send( _connection );
			
			foreach( CategoryInfo info in list.CategoryInfos )
			{
				foreach( CategoryValue cv in info.Children )
				{
					Console.WriteLine( line + cv.KeyName + "(" + cv.KeyValue + ")" );
					DisplayTaxonomyItems( key, cv.KeyValue, tabs + 1 );
				}
			}
		}

	}
}
