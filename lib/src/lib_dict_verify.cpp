#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <cstring>
#include <cstdlib>
#include <glib/gstdio.h>
#include <glib.h>
#include <string>
#include <vector>

#ifdef _WIN32
#  include <windows.h>
#else
#  include <unistd.h>
#endif

#include "lib_dict_verify.h"
#include "libcommon.h"
#include "lib_res_store.h"
#include "lib_binary_dict_parser.h"

/* Terminology

Index file is a sequence of index items.
An index item consists of:
word - the key of the item;
size and offset of data block containing definition in the dictionary file.
A data block consists of a number of fields.
A field has a type specified by type identifier (one character, an ASCII letter).
*/

VerifResult stardict_verify(const char *ifofilename)
{
	VerifResult result = VERIF_RESULT_OK;

	g_message("Verifying dictionary '%s'...", ifofilename);
	glib::CharStr cdirname(g_path_get_dirname(ifofilename));
	resource_storage res_storage;
	res_storage.load(get_impl(cdirname));
	result = combine_result(result, res_storage.get_verif_result());

	binary_dict_parser_t dict;
	result = combine_result(result, dict.load(ifofilename, static_cast<i_resource_storage*>(&res_storage)));

	if(result == VERIF_RESULT_OK)
		g_message("Dictionary '%s'. Verification result: OK.", ifofilename);
	else if(result < VERIF_RESULT_CRITICAL)
		g_message("Dictionary '%s'. Verification result: Non-critical problems were found. The dictionary is safe to use.", ifofilename);
	else
		g_message("Dictionary '%s'. Verification result: The dictionary is broken. Do not use it.", ifofilename);
	return result;
}
