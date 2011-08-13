//
// "$Id: file.cxx 8870 2011-07-26 21:19:35Z matt $"
//
// Fluid file routines for the Fast Light Tool Kit (FLTK).
//
// You may find the basic read_* and write_* routines to
// be useful for other programs.  I have used them many times.
// They are somewhat similar to tcl, using matching { and }
// to quote strings.
//
// Copyright 1998-2010 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "Fl_Type.h"
#include "../fltk3/filename.h"


extern const char *filename;
extern const char *DOS_path(const char *filename);

// ------------ VisualC 2008 ---------------------------------------------------

int write_fltk_ide_visualc2008() {
  // for now, we use a template file in FLTK/ide/templates/VisualC2008.tmpl .
  // When done, everything will likely be integrated into the executable to make one compact package.
  char buf[2048], base_dir[2048], tgt_base[2048];
  strcpy(base_dir, filename);
  *((char*)fltk3::filename_name(base_dir)) = 0; // keep only the path
  strcpy(tgt_base, base_dir);
  strcpy(buf, base_dir);
  strcat(buf, "ide/templates/VisualC2008.tmpl");
  FILE *out = stdout;
  FILE *in = fopen(buf, "rb");
  
  for (;;) {
    if (fgets(buf, 2047, in)==0) // FIXME: handle error!
      break;
    char *hash = buf-1;
    char copyLine = 1;
    for (;;) {
      hash = strchr(hash+1, '#');
      if (!hash) break;
      if (hash && hash[1]=='#') { // double hash escapes the control character
        int n = strlen(hash);
        memmove(hash, hash+1, n);
        continue;
      } else { // single hash is a command
        copyLine = 0;
        if (strncmp(hash, "#WriteFile(",11)==0) {
          // mark the end of the filename (this will crash if the formatting is wrong!)
          char *sep = strchr(hash, ')');
          *sep = 0;
          // filename is relative, so add it to the base_dir
          char fnbuf[2048];
          strcpy(fnbuf, base_dir);
          strcat(fnbuf, hash+11);
          out = fopen(fnbuf, "wb");
          // set the filepath for this target. In this module, all filenames are relative to the Makefile
          strcpy(tgt_base, fnbuf);
          *((char*)fltk3::filename_name(tgt_base)) = 0; // keep only the path
                                                        // restore buffer and continue 
          *sep = ')';
          hash = strchr(hash, ';')+1;
        } else if (strncmp(hash, "#CloseFile", 10)==0) {
          if (out!=stdout) fclose(out);
          out = stdout;
          // set the filepath for the default target. 
          strcpy(tgt_base, base_dir);
          hash = strchr(hash, ';')+1;
        } else if (strncmp(hash, "#SourceFiles(", 13)==0) {
          Fl_Type *tgt = Fl_Target_Type::find(hash+13, ')'); // keep tgt local
          if (!tgt) {
            printf("ERROR writing VisualC 2008 file: target not found!");
            return -1;
          }
          Fl_File_Type *f;
          for (f = Fl_File_Type::first_file(tgt); f; f = f->next_file(tgt)) {
            if (f->file_is_code() && f->builds_in(FL_ENV_VC2008)) {
              fprintf(out, "\t\t<File\r\n");
              fprintf(out, "\t\t\tRelativePath=\"..\\..\\%s\"\r\n", DOS_path(f->filename()));
              fprintf(out, "\t\t\t>\r\n");
              fprintf(out, "\t\t\t<FileConfiguration\r\n");
              fprintf(out, "\t\t\t\tName=\"Debug|Win32\"\r\n");
              fprintf(out, "\t\t\t\t>\r\n");
              fprintf(out, "\t\t\t\t<Tool\r\n");
              fprintf(out, "\t\t\t\t\tName=\"VCCLCompilerTool\"\r\n");
              fprintf(out, "\t\t\t\t\tOptimization=\"0\"\r\n");
              fprintf(out, "\t\t\t\t\tAdditionalIncludeDirectories=\"\"\r\n");
              fprintf(out, "\t\t\t\t\tPreprocessorDefinitions=\"\"\r\n");
              fprintf(out, "\t\t\t\t/>\r\n");
              fprintf(out, "\t\t\t</FileConfiguration>\r\n");
              fprintf(out, "\t\t\t<FileConfiguration\r\n");
              fprintf(out, "\t\t\t\tName=\"Release|Win32\"\r\n");
              fprintf(out, "\t\t\t\t>\r\n");
              fprintf(out, "\t\t\t\t<Tool\r\n");
              fprintf(out, "\t\t\t\t\tName=\"VCCLCompilerTool\"\r\n");
              fprintf(out, "\t\t\t\t\tFavorSizeOrSpeed=\"0\"\r\n");
              fprintf(out, "\t\t\t\t\tAdditionalIncludeDirectories=\"\"\r\n");
              fprintf(out, "\t\t\t\t\tPreprocessorDefinitions=\"\"\r\n");
              fprintf(out, "\t\t\t\t/>\r\n");
              fprintf(out, "\t\t\t</FileConfiguration>\r\n");
              fprintf(out, "\t\t\t<FileConfiguration\r\n");
              fprintf(out, "\t\t\t\tName=\"Debug Cairo|Win32\"\r\n");
              fprintf(out, "\t\t\t\t>\r\n");
              fprintf(out, "\t\t\t\t<Tool\r\n");
              fprintf(out, "\t\t\t\t\tName=\"VCCLCompilerTool\"\r\n");
              fprintf(out, "\t\t\t\t\tOptimization=\"0\"\r\n");
              fprintf(out, "\t\t\t\t\tAdditionalIncludeDirectories=\"\"\r\n");
              fprintf(out, "\t\t\t\t\tPreprocessorDefinitions=\"\"\r\n");
              fprintf(out, "\t\t\t\t/>\r\n");
              fprintf(out, "\t\t\t</FileConfiguration>\r\n");
              fprintf(out, "\t\t\t<FileConfiguration\r\n");
              fprintf(out, "\t\t\t\tName=\"Release Cairo|Win32\"\r\n");
              fprintf(out, "\t\t\t\t>\r\n");
              fprintf(out, "\t\t\t\t<Tool\r\n");
              fprintf(out, "\t\t\t\t\tName=\"VCCLCompilerTool\"\r\n");
              fprintf(out, "\t\t\t\t\tFavorSizeOrSpeed=\"0\"\r\n");
              fprintf(out, "\t\t\t\t\tAdditionalIncludeDirectories=\"\"\r\n");
              fprintf(out, "\t\t\t\t\tPreprocessorDefinitions=\"\"\r\n");
              fprintf(out, "\t\t\t\t/>\r\n");
              fprintf(out, "\t\t\t</FileConfiguration>\r\n");
              fprintf(out, "\t\t</File>\r\n");                        
            }
          }
          hash = strchr(hash, ';')+1;
        } else if (strncmp(hash, "#HeaderFiles(", 13)==0) {
          Fl_Type *tgt = Fl_Target_Type::find(hash+13, ')'); // keep tgt local
          if (!tgt) {
            printf("ERROR writing VisualC 2008 file: target not found!");
            return -1;
          }
          Fl_File_Type *f;
          for (f = Fl_File_Type::first_file(tgt); f; f = f->next_file(tgt)) {
            if (f->file_is_header() && f->lists_in(FL_ENV_VC2008)) {
              fprintf(out, "\t\t\t<File\r\n");
              fprintf(out, "\t\t\t\tRelativePath=\"..\\..\\%s\"\r\n", DOS_path(f->filename()));
              fprintf(out, "\t\t\t\t>\r\n");
              // OK, we have cheated here quite a bit. The stuff missing here (as opposed to "#SourceFiles"
              // depends on "builds_in", and not on the fact of being a header file. But for now it does
              // what we expect...
              fprintf(out, "\t\t\t</File>\r\n");                        
            }
          }
          hash = strchr(hash, ';')+1;
        } else {
          printf("Unknown command in template: <<%s>>\n", hash);
          copyLine = 1;
          hash++;
        }
      }
    }
    if (copyLine) fputs(buf, out);
  }
  
  fclose(in);
  if (out!=stdout) fclose(out);
  
  return 0;
}


//
// End of "$Id: file.cxx 8870 2011-07-26 21:19:35Z matt $".
//
