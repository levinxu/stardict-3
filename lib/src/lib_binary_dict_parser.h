#ifndef LIB_BINARY_DICT_PARSER_H_
#define LIB_BINARY_DICT_PARSER_H_

#include <string>
#include <vector>
#include "libcommon.h"
#include "ifo_file.h"
#include "lib_dict_data_block.h"
#include "lib_res_store.h"
#include "lib_dict_verify.h"

struct worditem_t {
	std::string word;
	guint32 offset;
	guint32 size;
};

struct synitem_t {
	std::string word;
	guint32 index;
};

class i_resource_storage;

class binary_dict_parser_t
{
public:
	typedef std::vector<worditem_t> worditem_vect_t;
	typedef std::vector<synitem_t> synitem_vect_t;

	binary_dict_parser_t(void);
	VerifResult load(const std::string& ifofilename,
			i_resource_storage* p_res_storage = NULL);
	void set_fix_errors(bool b)
	{
		fix_errors = b;
	}
	bool get_fix_errors(void) const
	{
		return fix_errors;
	}
	const worditem_vect_t& get_worditems(void) const
	{
		return index;
	}
	const synitem_vect_t& get_synitems(void) const
	{
		return synindex;
	}
	const DictInfo& get_dict_info(void) const
	{
		return dict_info;
	}
	int get_data_fields(guint32 offset, guint32 size, data_field_vect_t& fields) const;

private:
	VerifResult prepare_idx_file(void);
	VerifResult prepare_dict_file(void);
	int load_ifo_file(void);
	VerifResult load_idx_file(void);
	VerifResult load_syn_file(void);
	VerifResult load_dict_file(void);
	VerifResult verify_data_blocks_overlapping(void);

	std::string basefilename;
	std::string ifofilename;
	std::string idxfilename; // file to read, uncompressed
	std::string idxfilename_orig; // may be archive
	std::string dictfilename;
	std::string dictfilename_orig;
	std::string synfilename;
	DictInfo dict_info;
	TempFile idxtemp;
	TempFile dicttemp;
	clib::File dictfile;
	guint32 dictfilesize;
	std::vector<worditem_t> index;
	std::vector<synitem_t> synindex;
	i_resource_storage* p_res_storage;
	/* fix errors if possible. We never change the files we read,
	 * all fixes effect only in-memory data structures.
	 * If an error is fixed, we do not return failure status,
	 * but an error message is printed nevertheless. */
	bool fix_errors;
};


#endif /* LIB_BINARY_DICT_PARSER_H_ */
