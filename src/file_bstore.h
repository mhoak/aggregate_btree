/*
    Aggregate btree implementation
    Copyright (C) 2012 Jeremy Bruestle

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, version 3.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __file_bstore_h__
#define __file_bstore_h__

#include <boost/thread.hpp>
#include <vector>
#include <map>

#include "vector_io.h"
#include "file_io.h"
#include "serial.h"

class file_bstore
{
	const static off_t k_goal_slab_size = 100*1024;  // 100 Kb slabs

	struct file_info
	{
		std::string name;
		file_io* io;
	};
	
	typedef std::map<off_t, file_info> slabs_t;
	typedef boost::recursive_mutex mutex_t;
	typedef boost::unique_lock<mutex_t> lock_t;

public:
	// Direct user API
	file_bstore();
	~file_bstore();
	void open(const std::string& dir, bool create = false);  // Opens, maybe creates
	void close();  // Closes a bstroe

	// Required API to bcache
	off_t write_node(const std::vector<char>& record);
	void write_root(const std::string& name, const std::vector<char>& record);
	void read_node(off_t which, std::vector<char>& record);
	void read_root(const std::string& name, std::vector<char>& record);
	void clear_before(off_t lowest);

protected:
	void next_file(); // Create a new output file
	void add_file(const std::string& name); // Add a new i/o file

	// Finds roots during reload
	off_t find_root(const std::string& name, off_t offset, file_io* f);
	off_t find_root(const std::string& name);

	off_t write_record(char prefix, const std::vector<char>& record);  
	bool read_record(file_io* f, char& prefix, std::vector<char>& record);  
	bool read_record(off_t offset, char& prefix, std::vector<char>& record);  
	void safe_read_record(off_t offset, char req_prefix, std::vector<char>& record);

	off_t m_size;  // The current 'logical size'
	unsigned int m_next_slab;  // The next slab number to use
	std::string m_dir;  // The directory the slabs live in
	file_io* m_cur_slab;  // The current slab
	slabs_t m_slabs;  // All the slabs
	mutex_t m_mutex;  // IO mutex, could be per slab, but I'm lazy
};

#endif
