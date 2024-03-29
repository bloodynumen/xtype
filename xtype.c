/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2015 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_xtype.h"


/* If you declare any globals in php_xtype.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(xtype)
*/

/* True global resources - no need for thread safety here */
static int le_xtype;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("xtype.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_xtype_globals, xtype_globals)
    STD_PHP_INI_ENTRY("xtype.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_xtype_globals, xtype_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_xtype_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_xtype_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "xtype", arg);
	RETURN_STRINGL(strg, len, 0);
}
PHP_FUNCTION(xtype)
{
  struct EH {
    char e[32];
    char h[32];
  } eh[29]={
    {"bmp", "424D"},
    {"jpg", "FFD8FF"},
    {"mpg", "000001B3"},
    {"mpg", "000001BA"},
    {"pst", "2142444E"},
    {"rm", "2E524D46"},
    {"ram", "2E7261FD"},
    {"psd", "38425053"},
    {"dwg", "41433130"},
    {"avi", "41564920"},
    {"gif", "47494638"},
    {"tif", "49492A00"},
    {"mid", "4D546864"},
    {"zip", "504B0304"},
    {"rar", "52617221"},
    {"wav", "57415645"},
    {"mov", "6D6F6F76"},
    {"png", "89504E47"},
    {"qdf", "AC9EBD8F"},
    {"xls.or.doc", "D0CF11E0"},
    {"pwl", "E3828596"},
    {"wpd", "FF575043"},
    {"xml", "3C3F786D6C"},
    {"html", "68746D6C3E"},
    {"rtf", "7B5C727466"},
    {"pdf", "255044462D312E"},
    {"asf", "3026B2758E66CF11"},
    {"dbx", "CFAD12FEC5FD746F"},
    {"mdb", "5374616E64617264204A"},
  };


  FILE *fp;
  int filename_len;
  char *filename;
  char file_type[32];
  char head[32];
  int i,j,c,len;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &filename, &filename_len) == FAILURE) {
    RETURN_NULL();
  }

  if (!filename_len) {
    php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid filename");
    RETURN_NULL();
  }

  fp = fopen(filename, "rb");
  if (NULL == fp) {
    php_error_docref(NULL TSRMLS_CC, E_WARNING, "Invalid file");
    RETURN_NULL();
  }

  for (i = 0; i < 14; i ++) {
    c = fgetc(fp);
	if (c == EOF) {
		break;
	}
    sprintf(head + i*2, "%2X", (unsigned char)c);
    for (j=0; j<29; j++) {
      if (0 == strcmp(head, eh[j].h)) {
        sprintf(file_type, "%s", eh[j].e);
        fclose(fp);
        len = strlen(file_type);
        break;
      }
    }
    if (len) {
        break;
    }
  }

  if (!len) {
      fclose(fp);
  }

  RETURN_STRINGL(file_type, len, 1);

}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_xtype_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_xtype_init_globals(zend_xtype_globals *xtype_globals)
{
	xtype_globals->global_value = 0;
	xtype_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(xtype)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(xtype)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(xtype)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(xtype)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(xtype)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "xtype support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ xtype_functions[]
 *
 * Every user visible function must have an entry in xtype_functions[].
 */
const zend_function_entry xtype_functions[] = {
	PHP_FE(confirm_xtype_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(xtype,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in xtype_functions[] */
};
/* }}} */

/* {{{ xtype_module_entry
 */
zend_module_entry xtype_module_entry = {
	STANDARD_MODULE_HEADER,
	"xtype",
	xtype_functions,
	PHP_MINIT(xtype),
	PHP_MSHUTDOWN(xtype),
	PHP_RINIT(xtype),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(xtype),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(xtype),
	PHP_XTYPE_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_XTYPE
ZEND_GET_MODULE(xtype)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
