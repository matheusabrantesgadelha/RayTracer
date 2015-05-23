from fileutils import *

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
    sourceFile = open( args.srcFolder+"/"+args.className + '.cpp', 'w' )
    headerFile = open( args.srcFolder+"/"+args.className + '.hpp', 'w' )
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

