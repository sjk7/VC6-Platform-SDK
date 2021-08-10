For examples of generating VB ADO queries for schema attributes, see the
GetSchemaInfo VB sample.  Click the 'Next Query Sample' button.

The predetermined sample query strings include the following.

  (cn=Domain)
    Finds the schema class for a domain.
  (cn=Given-Name)
    Finds the schema attribute for first name.
  (IsSingleValued=FALSE)
    Finds all of the attributes in the schema which are multi-valued.
    Change the FALSE to TRUE to find all single-valued attributes.
  (ldapDisplayName=objectGUID)
    Finds the attribute for GUID by its LDAP name.
  (IsMemberOfPartialAttributeSet=TRUE)
    Finds the attributes that are stored in the Global Catalog.
  (searchFlags=1)
    Finds all indexed values.
    Change 1 to 0 (zero) to find all non-indexed values.
  (systemFlags=" + CStr(ADS_SYSTEMFLAG_ATTR_NOT_REPLICATED Or
   ADS_SYSTEMFLAG_ATTR_SCHEMA_BASE_OBJECT) + ")
    Finds all attributes that are unreplicated and match the base schema object.
  (systemFlags:1.2.840.113556.1.4.804:=" + CStr(ADS_SYSTEMFLAG_ATTR_IS_CONSTRUCTED) + ")
    Finds all constructed attributes.
  (subClassOf=organizationalPerson)
    Finds classes that are a subclass of organizationalPerson.

