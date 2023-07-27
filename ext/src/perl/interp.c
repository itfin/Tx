#include <EXTERN.h>               /* from the Perl distribution     */
 #include <perl.h>                 /* from the Perl distribution     */

 static PerlInterpreter *my_perl;  /***    The Perl interpreter    ***/
EXTERN_C void xs_init (pTHX);

EXTERN_C void boot_DynaLoader (pTHX_ CV* cv);

EXTERN_C void
xs_init(pTHX)
{
    static const char file[] = __FILE__;
    dXSUB_SYS;
    PERL_UNUSED_CONTEXT;

    /* DynaLoader is a special case */
    newXS("DynaLoader::boot_DynaLoader", boot_DynaLoader, file);
}


 int main(int argc, char **argv, char **env)
 {
   //	PERL_SYS_INIT3(&argc,&argv,&env);
        my_perl = perl_alloc();
        perl_construct(my_perl);
	PL_exit_flags |= PERL_EXIT_DESTRUCT_END;
        perl_parse(my_perl, xs_init, argc, argv, (char **)NULL);
        perl_run(my_perl);
        perl_destruct(my_perl);
        perl_free(my_perl);
	PERL_SYS_TERM();
	exit(EXIT_SUCCESS);
 }
