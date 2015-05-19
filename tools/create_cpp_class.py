import argparse
import fileinput

def writeHeaderClass( _file, _className ):
	defineName =  _className.upper() + "_H_"
	content =''' 
#ifndef {define_name} 
#define {define_name} 

class {class_name}
{{
}}

#endif
'''.format( define_name = defineName, class_name = _className )

	_file.write( content )

def writeSourceClass( _file, _className ):
	content = '''
#include "{class_name}.hpp"
'''.format( class_name = _className )

	_file.write(content)

def insertClassOnMakefile( _fileinput, _className, _folder ):
	for line in _fileinput:
		if line.startswith('OBJS'):
			print line[:-1] + " " + _className + ".o"
		elif line.startswith("clean"):
			objectCompilation = '''{class_name}.o: {folder}/{class_name}.cpp
\t$(CC) $(CFLAGS) -c {folder}/{class_name}.cpp $(INCLUDES)
'''.format( class_name = _className, folder = _folder )
			print objectCompilation
			print line,
		else:
			print line,

def isClassOnMakefile( _fileinput, _className ):
	for line in _fileinput:
		if line.startswith(_className+'.o'):
			return True
	return False

def main():
	parser = argparse.ArgumentParser( 
			description = "Create c++ classes with source and header files." )
	parser.add_argument(
			'className',
			type=str,
			help="Name of the class to be created"
			)
	parser.add_argument(
			'srcFolder',
			type=str,
			help="Folder containing the source code",
			default="src"
			)
	args = parser.parse_args()
	sourceFile = open( args.className + '.cpp', 'w' )
	headerFile = open( args.className + '.hpp', 'w' )
	makefile = open( "Makefile", 'r' )

	if( isClassOnMakefile( makefile, args.className ) ):
		print( "A class with this name exists in the provided Makefile." )
	else:
		writeHeaderClass( headerFile, args.className )
		writeSourceClass( sourceFile, args.className )

		makefile.close()
		makefileDataInput = fileinput.input( "Makefile", inplace=1 )
		insertClassOnMakefile( makefileDataInput, args.className, args.srcFolder )

if __name__ == "__main__":
	main()

