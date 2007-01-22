// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*- 
/*
 * Ceph - scalable distributed file system
 *
 * Copyright (C) 2004-2006 Sage Weil <sage@newdream.net>
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1, as published by the Free Software 
 * Foundation.  See file COPYING.
 * 
 */

#ifndef __EINODEUPDATE_H
#define __EINODEUPDATE_H

#include <assert.h>
#include "config.h"
#include "include/types.h"

#include "../LogEvent.h"
#include "ETrace.h"


class EInodeUpdate : public LogEvent {
 protected:
  ETrace trace;

 public:
  EInodeUpdate(CInode *in) : LogEvent(EVENT_INODEUPDATE),
			     trace(in) {
  }
  EInodeUpdate() : LogEvent(EVENT_INODEUPDATE) { }
  
  void print(ostream& out) {
    out << "up inode " << trace.back().inode.ino 
	<< " " << trace 
	<< " v " << trace.back().inode.version;    
  }
  
  virtual void encode_payload(bufferlist& bl) {
    trace.encode(bl);
  }
  void decode_payload(bufferlist& bl, int& off) {
    trace.decode(bl, off);
  }

  bool can_expire(MDS *mds);
  void retire(MDS *mds, Context *c);
  bool has_happened(MDS *mds);  
  void replay(MDS *mds);

};

#endif
