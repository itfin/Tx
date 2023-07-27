/* A simple, yet complete Mathematica frontend by S.C.Sheridan
 *
 * To run this program use the command-line below:
 *	Unix:    fe  -linkname "math -mathlink"
 *	Mac:     fe  -linkname "'Hard Drive:Mathematica 2.2.2:Mathematica Kernel' -mathlink"
 *	Windows: fe  -linkname "c:\wnmath22\math -mathlink"
 *
 * There is no way yet to send an interrupt to the kernel using
 * this frontend.  So if you want to see how interrupt menus work,
 * you can generate one by evaluating Interrupt[].  Try evaluating:
 *
 *   While[True, Interrupt[]]
 *
 * This frontend does not display plots.  However, if you evaluate:
 *
 *  $Display = "stdout"
 *
 * then PostScript will be sent to this frontend and it will concatenate
 * a PostScript cell to the end of a notebook named "pictures.ma". (This
 * was Thomas Chin's idea.)  You can open this notebook using the Notebook
 * frontend to see the images.
 */


#include <stdio.h>
#include <string.h>

#include "mathlink.h"

MLINK	link;
FILE *picture_book;
int	dialog_level;
int check_error( void);



#undef TRUE
#undef FALSE
#define TRUE 1
#define FALSE 0



char* ps_cellheader =  ":[font = postscript; PostScript; formatAsPostScript; output; inactive;"
                       "pictureLeft = 100; pictureWidth = 300; pictureHeight = 300;]\n";
char* notebook_header = "(*^\n\n::[\n]\n";
char* notebook_trailer = "^*)";

int eval_and_print (char * input_string){
	static enum { expression_expected, string_expected} input_mode;
	static int first_PS_piece = TRUE;
	static int verbose_menu_coming = FALSE;

	int	packet, interrupt_menu;
	char* output_string;
	int	syntax_error_position = -1;
	int	done = FALSE;

	if( input_string){
		if( input_mode == expression_expected)
			MLPutFunction( link, "EnterTextPacket", 1);
		else{
			MLPutFunction( link, "TextPacket", 1);
			input_mode = expression_expected;
		}
		MLPutString( link, input_string);
		MLEndPacket( link);
		if( check_error()) return 0;
	}

	while( !done)
		{
		switch( packet = MLNextPacket( link)){
		case ILLEGALPKT:
			if( !MLClearError( link) || !MLNewPacket(link))
				done = TRUE;
			break;

		case INPUTNAMEPKT:
		case INPUTPKT:
			if( MLGetString( link, &output_string)){
				printf( "%s", output_string);
				MLDisownString( link, output_string);
			}
			done = TRUE;
			break;

		case TEXTPKT:
			if( MLGetString( link, &output_string)){
				printf( "%s\n", output_string);
				MLDisownString( link, output_string);
			}
			if( verbose_menu_coming){
				verbose_menu_coming = FALSE;
				printf( "\n%s", input_string);
				done = TRUE;
			}
			break;

		case OUTPUTNAMEPKT:
		case RETURNTEXTPKT:
			if( MLGetString( link, &output_string)){
				printf( "%s\n", output_string);
				MLDisownString( link, output_string);
			}
			break;

		case DISPLAYPKT:
			if( MLGetString( link, &output_string)){
				if( first_PS_piece){
					first_PS_piece = FALSE;
					if( picture_book)
						fprintf( picture_book, "%s", ps_cellheader);
				}
				if( picture_book)
					fprintf( picture_book, "%s", output_string);
				MLDisownString( link, output_string);
			}
			break;

		case DISPLAYENDPKT:
			if( MLGetString( link, &output_string)){
				if( picture_book)
					fprintf( picture_book, "%s", output_string);
				MLDisownString( link, output_string);
			}
			first_PS_piece = TRUE;
			break;

		case SYNTAXPKT:
			MLGetInteger( link, &syntax_error_position);
			printf( "%s\n", input_string);
			memset( input_string, ' ', syntax_error_position);
			printf( "%.*s^ Syntax Error\n", syntax_error_position, input_string);
			break;


		case INPUTSTRPKT:
			if( MLGetString( link, &output_string)){
				printf( "%s", output_string);
				MLDisownString( link, output_string);
			}
			input_mode = string_expected;
			done = TRUE;
			break;

		case MENUPKT:
			MLGetInteger( link, &interrupt_menu);
			if( MLGetString( link, &output_string)){
				strcpy( input_string, output_string);
				MLDisownString( link, output_string);
			}
			input_mode = string_expected;
			if( interrupt_menu == 0)
				verbose_menu_coming = TRUE;
			else{
				printf( "%s", input_string);
				done = TRUE;
			}
			break;

		case MESSAGEPKT:
			MLNewPacket( link);
			/* beep */
			break;

		case SUSPENDPKT:
			MLNewPacket( link);
			printf( "--suspended--\n");
			done = TRUE;
			break;

		case RESUMEPKT:
			printf( "--resumed--\n");
			MLNewPacket( link);
			break;

		case BEGINDLGPKT:
			MLGetInteger( link, &dialog_level);
			printf( "entering dialog:%d\n", dialog_level);
			break;

		case ENDDLGPKT:
			MLGetInteger( link, &dialog_level);
			dialog_level--;
			printf( "leaving dialog:%d\n", dialog_level);
			break;
		}

		MLNewPacket( link);
		if( check_error()) return 0;
	}

	return( packet);
}



void send_interrupt( void){
	if( link) MLPutMessage( link, MLInterruptMessage);
}



int check_error( void){
	int		result;

	if( link == (MLINK)0) return MLEDEAD;

	if( result = MLError( link)){
		printf( "\nMathLink Error: %s\n", MLErrorMessage( link));
		MLClose( link);
		link = (MLINK)0;
	}

	return result;
}



int main( int argc, char* argv[]){
	static char buff[512];
	MLEnvironment ep;

	ep = MLInitialize( (MLParametersPointer)0);
	if( ep == (MLParametersPointer)0) goto R0;

	link = MLOpen( argc, argv);
	if( link == (MLINK)0) goto R1;

	if( !MLConnect( link)) goto R2;

	if( picture_book = fopen( "pictures.ma", "rb+"))
		fseek( picture_book, -1 * (long)strlen(notebook_trailer), SEEK_END);
	else if(picture_book = fopen( "pictures.ma", "wb"))
		fprintf( picture_book, "%s", notebook_header);


	eval_and_print( NULL);

	while( TRUE){
		gets( buff);
		if( ! eval_and_print( buff)) break;
	}

	if( picture_book)
		fprintf( picture_book, notebook_trailer);
	
R2:	if( link) MLClose( link);
R1:	MLDeinitialize( ep);
R0:	return 0;
}
