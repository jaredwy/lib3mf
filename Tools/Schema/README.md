This folder contains the XML Schema Document Specifications for the
 core, material, production, slice and beamlattice
extensions to 3MF.

_Usage:_
1. Run prepare.bat
2. Run `..\xmllint\xmllint.exe --schema test\core_2015_02_with_extensions.xsd model.xml --noout`
    - test\core_2015_02_with_extensions.xsd is the schema of the core extension which has other extensions (slice, materials, and beamlattice) included and was generated by prepare.bat
    - model.xml is the extracted 3dmodel.model file from the 3MF you want to validate

_Important Notes:_
 - production.xsd seems to be broken
	1. production_2015_06.xsd:33: element simpleType: Schemas parser error : Element '{http://www.w3.org/2001/XMLSchema}attribute': The attribute 'type' and the <simpleType> child are mutually exclusive. WXS schema wrapper.xsd failed to compile
	2. ST_ResourceID, mesh, components, ST_ObjectType, ST_ResourceIndex, ST_UriReference and ID are not defined/imported properly
   Therefore, it is currently excluded from the validation.
 - The value "2147483647" for maxOccurs does not work with xmllint. In order to use xmllint, repalce "2147483647" with "1073741824" (=2^31) in all .xsd-files in order to validate a file.
 - In contrast to the embedded xsd in the CoreSpec of 3MF, the build->items in the file core_2015_02.xsd has an attribute "partnumber". This is in alignment with the text of the CoreSpec and the implementation in 3MF. This should be updated in the embedded xsd of the CoreSpec of 3MF.