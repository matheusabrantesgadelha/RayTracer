import argparse
import fileinput
from create_cpp_class import isClassOnMakefile, insertClassOnMakefile

def main():
    parser = argparse.ArgumentParser( 
            description = "Inserts a source code to the makefile." )
    parser.add_argument(
            'sourceName',
            type=str,
            help="Name of the source to be inserted (without .cpp)"
            )
    parser.add_argument(
            'srcFolder',
            type=str,
            help="Folder containing the source code",
            default="src"
            )   
    args = parser.parse_args()
    makefile = open( "Makefile", 'r' )

    if( isClassOnMakefile( makefile, args.sourceName ) ):
        print( "A source with this name exists in the provided Makefile." )
    else:
        makefile.close()
        makefileDataInput = fileinput.input( "Makefile", inplace=1 )
        insertClassOnMakefile( makefileDataInput, args.sourceName, args.srcFolder )

if __name__ == "__main__":
    main()

