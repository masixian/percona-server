/* Copyright (C) 2018 Percona

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
   USA */

#ifndef _HA_TOKUPART_H
#define _HA_TOKUPART_H

#include "sql/partitioning/partition_base.h"

/* This class must contain engine-specific functions for partitioning */
class ha_tokupart : public native_part::Partition_base {
 public:
  ha_tokupart(handlerton *hton, TABLE_SHARE *table_arg)
      : Partition_base(hton, table_arg){};

  ha_tokupart(handlerton *hton, TABLE_SHARE *table_arg,
              partition_info *part_info,
              native_part::Partition_base *clone_base, MEM_ROOT *clone_mem_root)
      : native_part::Partition_base(hton, table_arg, clone_base,
                                    clone_mem_root) {
    this->get_partition_handler()->set_part_info(part_info, true);
  }

  ~ha_tokupart() override {}

  enum row_type get_partition_row_type(const dd::Table *, uint) override {
    return ROW_TYPE_NOT_USED;
  }

 private:
  handler *get_file_handler(TABLE_SHARE *share, MEM_ROOT *alloc) const override;
  handler *clone(const char *name, MEM_ROOT *mem_root) override;
  ulong index_flags(uint inx, uint part, bool all_parts) const override;

  bool rpl_lookup_rows() override;
};

#endif  // _HA_TOKUPART_H
