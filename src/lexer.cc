/* Generated by re2c 0.16 */
// Copyright 2011 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "lexer.h"

#include <stdio.h>

#include "eval_env.h"
#include "util.h"

bool Lexer::Error(const string& message, string* err) {
  // Compute line/column.
  int line = 1;
  const char* context = input_.str_;
  for (const char* p = input_.str_; p < last_token_; ++p) {
    if (*p == '\n') {
      ++line;
      context = p + 1;
    }
  }
  int col = last_token_ ? (int)(last_token_ - context) : 0;

  char buf[1024];
  snprintf(buf, sizeof(buf), "%s:%d: ", filename_.AsString().c_str(), line);
  *err = buf;
  *err += message + "\n";

  // Add some context to the message.
  const int kTruncateColumn = 72;
  if (col > 0 && col < kTruncateColumn) {
    int len;
    bool truncated = true;
    for (len = 0; len < kTruncateColumn; ++len) {
      if (context[len] == 0 || context[len] == '\n') {
        truncated = false;
        break;
      }
    }
    *err += string(context, len);
    if (truncated)
      *err += "...";
    *err += "\n";
    *err += string(col, ' ');
    *err += "^ near here";
  }

  return false;
}

Lexer::Lexer(const char* input) {
  Start("input", input);
}

void Lexer::Start(StringPiece filename, StringPiece input) {
  filename_ = filename;
  input_ = input;
  ofs_ = input_.str_;
  last_token_ = NULL;
}

const char* Lexer::TokenName(Token t) {
  switch (t) {
  case ERROR:    return "lexing error";
  case BUILD:    return "'build'";
  case COLON:    return "':'";
  case DEFAULT:  return "'default'";
  case EQUALS:   return "'='";
  case IDENT:    return "identifier";
  case INCLUDE:  return "'include'";
  case INDENT:   return "indent";
  case NEWLINE:  return "newline";
  case PIPE2:    return "'||'";
  case PIPE:     return "'|'";
  case POOL:     return "'pool'";
  case RULE:     return "'rule'";
  case SUBNINJA: return "'subninja'";
  case TEOF:     return "eof";
  case UTIL:     return "util";
  }
  return NULL;  // not reached
}

const char* Lexer::TokenErrorHint(Token expected) {
  switch (expected) {
  case COLON:
    return " ($ also escapes ':')";
  default:
    return "";
  }
}

string Lexer::DescribeLastError() {
  if (last_token_) {
    switch (last_token_[0]) {
    case '\t':
      return "tabs are not allowed, use spaces";
    }
  }
  return "lexing error";
}

void Lexer::UnreadToken() {
  ofs_ = last_token_;
}

Lexer::Token Lexer::ReadToken() {
  const char* p = ofs_;
  const char* q;
  const char* start;
  Lexer::Token token;
  for (;;) {
    start = p;
    
{
	unsigned char yych;
	unsigned int yyaccept = 0;
	static const unsigned char yybm[] = {
		  0, 128, 128, 128, 128, 128, 128, 128, 
		128, 128,   0, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		160, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 192, 192, 128, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 128, 128, 128, 128, 128, 128, 
		128, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 128, 128, 128, 128, 192, 
		128, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 192, 192, 192, 192, 192, 
		192, 192, 192, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
	};
	yych = *p;
	if (yybm[0+yych] & 32) {
		goto yy9;
	}
	if (yych <= '_') {
		if (yych <= '.') {
			if (yych <= '\f') {
				if (yych <= 0x00) goto yy2;
				if (yych == '\n') goto yy6;
				goto yy4;
			} else {
				if (yych <= '"') {
					if (yych <= '\r') goto yy8;
					goto yy4;
				} else {
					if (yych <= '#') goto yy12;
					if (yych <= ',') goto yy4;
					goto yy13;
				}
			}
		} else {
			if (yych <= '<') {
				if (yych <= '/') goto yy4;
				if (yych <= '9') goto yy13;
				if (yych <= ':') goto yy16;
				goto yy4;
			} else {
				if (yych <= '@') {
					if (yych <= '=') goto yy18;
					goto yy4;
				} else {
					if (yych <= 'Z') goto yy13;
					if (yych <= '^') goto yy4;
					goto yy13;
				}
			}
		}
	} else {
		if (yych <= 'p') {
			if (yych <= 'c') {
				if (yych <= '`') goto yy4;
				if (yych == 'b') goto yy20;
				goto yy13;
			} else {
				if (yych <= 'h') {
					if (yych <= 'd') goto yy21;
					goto yy13;
				} else {
					if (yych <= 'i') goto yy22;
					if (yych <= 'o') goto yy13;
					goto yy23;
				}
			}
		} else {
			if (yych <= 't') {
				if (yych <= 'q') goto yy13;
				if (yych <= 'r') goto yy24;
				if (yych <= 's') goto yy25;
				goto yy13;
			} else {
				if (yych <= 'z') {
					if (yych <= 'u') goto yy26;
					goto yy13;
				} else {
					if (yych == '|') goto yy27;
					goto yy4;
				}
			}
		}
	}
yy2:
	++p;
	{ token = TEOF;     break; }
yy4:
	++p;
yy5:
	{ token = ERROR;    break; }
yy6:
	++p;
	{ token = NEWLINE;  break; }
yy8:
	yych = *++p;
	if (yych == '\n') goto yy29;
	goto yy5;
yy9:
	yyaccept = 0;
	q = ++p;
	yych = *p;
	if (yybm[0+yych] & 32) {
		goto yy9;
	}
	if (yych <= '\f') {
		if (yych == '\n') goto yy6;
	} else {
		if (yych <= '\r') goto yy31;
		if (yych == '#') goto yy33;
	}
yy11:
	{ token = INDENT;   break; }
yy12:
	yyaccept = 1;
	yych = *(q = ++p);
	if (yych <= 0x00) goto yy5;
	goto yy34;
yy13:
	++p;
	yych = *p;
yy14:
	if (yybm[0+yych] & 64) {
		goto yy13;
	}
	{ token = IDENT;    break; }
yy16:
	++p;
	{ token = COLON;    break; }
yy18:
	++p;
	{ token = EQUALS;   break; }
yy20:
	yych = *++p;
	if (yych == 'u') goto yy37;
	goto yy14;
yy21:
	yych = *++p;
	if (yych == 'e') goto yy38;
	goto yy14;
yy22:
	yych = *++p;
	if (yych == 'n') goto yy39;
	goto yy14;
yy23:
	yych = *++p;
	if (yych == 'o') goto yy40;
	goto yy14;
yy24:
	yych = *++p;
	if (yych == 'u') goto yy41;
	goto yy14;
yy25:
	yych = *++p;
	if (yych == 'u') goto yy42;
	goto yy14;
yy26:
	yych = *++p;
	if (yych == 't') goto yy43;
	goto yy14;
yy27:
	++p;
	if ((yych = *p) == '|') goto yy44;
	{ token = PIPE;     break; }
yy29:
	++p;
	{ token = NEWLINE;  break; }
yy31:
	yych = *++p;
	if (yych == '\n') goto yy29;
yy32:
	p = q;
	if (yyaccept == 0) {
		goto yy11;
	} else {
		goto yy5;
	}
yy33:
	++p;
	yych = *p;
yy34:
	if (yybm[0+yych] & 128) {
		goto yy33;
	}
	if (yych <= 0x00) goto yy32;
	++p;
	{ continue; }
yy37:
	yych = *++p;
	if (yych == 'i') goto yy46;
	goto yy14;
yy38:
	yych = *++p;
	if (yych == 'f') goto yy47;
	goto yy14;
yy39:
	yych = *++p;
	if (yych == 'c') goto yy48;
	goto yy14;
yy40:
	yych = *++p;
	if (yych == 'o') goto yy49;
	goto yy14;
yy41:
	yych = *++p;
	if (yych == 'l') goto yy50;
	goto yy14;
yy42:
	yych = *++p;
	if (yych == 'b') goto yy51;
	goto yy14;
yy43:
	yych = *++p;
	if (yych == 'i') goto yy52;
	goto yy14;
yy44:
	++p;
	{ token = PIPE2;    break; }
yy46:
	yych = *++p;
	if (yych == 'l') goto yy53;
	goto yy14;
yy47:
	yych = *++p;
	if (yych == 'a') goto yy54;
	goto yy14;
yy48:
	yych = *++p;
	if (yych == 'l') goto yy55;
	goto yy14;
yy49:
	yych = *++p;
	if (yych == 'l') goto yy56;
	goto yy14;
yy50:
	yych = *++p;
	if (yych == 'e') goto yy58;
	goto yy14;
yy51:
	yych = *++p;
	if (yych == 'n') goto yy60;
	goto yy14;
yy52:
	yych = *++p;
	if (yych == 'l') goto yy61;
	goto yy14;
yy53:
	yych = *++p;
	if (yych == 'd') goto yy63;
	goto yy14;
yy54:
	yych = *++p;
	if (yych == 'u') goto yy65;
	goto yy14;
yy55:
	yych = *++p;
	if (yych == 'u') goto yy66;
	goto yy14;
yy56:
	++p;
	if (yybm[0+(yych = *p)] & 64) {
		goto yy13;
	}
	{ token = POOL;     break; }
yy58:
	++p;
	if (yybm[0+(yych = *p)] & 64) {
		goto yy13;
	}
	{ token = RULE;     break; }
yy60:
	yych = *++p;
	if (yych == 'i') goto yy67;
	goto yy14;
yy61:
	++p;
	if (yybm[0+(yych = *p)] & 64) {
		goto yy13;
	}
	{ token = UTIL;     break; }
yy63:
	++p;
	if (yybm[0+(yych = *p)] & 64) {
		goto yy13;
	}
	{ token = BUILD;    break; }
yy65:
	yych = *++p;
	if (yych == 'l') goto yy68;
	goto yy14;
yy66:
	yych = *++p;
	if (yych == 'd') goto yy69;
	goto yy14;
yy67:
	yych = *++p;
	if (yych == 'n') goto yy70;
	goto yy14;
yy68:
	yych = *++p;
	if (yych == 't') goto yy71;
	goto yy14;
yy69:
	yych = *++p;
	if (yych == 'e') goto yy73;
	goto yy14;
yy70:
	yych = *++p;
	if (yych == 'j') goto yy75;
	goto yy14;
yy71:
	++p;
	if (yybm[0+(yych = *p)] & 64) {
		goto yy13;
	}
	{ token = DEFAULT;  break; }
yy73:
	++p;
	if (yybm[0+(yych = *p)] & 64) {
		goto yy13;
	}
	{ token = INCLUDE;  break; }
yy75:
	yych = *++p;
	if (yych != 'a') goto yy14;
	++p;
	if (yybm[0+(yych = *p)] & 64) {
		goto yy13;
	}
	{ token = SUBNINJA; break; }
}

  }

  last_token_ = start;
  ofs_ = p;
  if (token != NEWLINE && token != TEOF)
    EatWhitespace();
  return token;
}

bool Lexer::PeekToken(Token token) {
  Token t = ReadToken();
  if (t == token)
    return true;
  UnreadToken();
  return false;
}

void Lexer::EatWhitespace() {
  const char* p = ofs_;
  const char* q;
  for (;;) {
    ofs_ = p;
    
{
	unsigned char yych;
	static const unsigned char yybm[] = {
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		128,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
	};
	yych = *p;
	if (yybm[0+yych] & 128) {
		goto yy84;
	}
	if (yych <= 0x00) goto yy80;
	if (yych == '$') goto yy87;
	goto yy82;
yy80:
	++p;
	{ break; }
yy82:
	++p;
yy83:
	{ break; }
yy84:
	++p;
	yych = *p;
	if (yybm[0+yych] & 128) {
		goto yy84;
	}
	{ continue; }
yy87:
	yych = *(q = ++p);
	if (yych == '\n') goto yy88;
	if (yych == '\r') goto yy90;
	goto yy83;
yy88:
	++p;
	{ continue; }
yy90:
	yych = *++p;
	if (yych == '\n') goto yy92;
	p = q;
	goto yy83;
yy92:
	++p;
	{ continue; }
}

  }
}

bool Lexer::ReadIdent(string* out) {
  const char* p = ofs_;
  for (;;) {
    const char* start = p;
    
{
	unsigned char yych;
	static const unsigned char yybm[] = {
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0, 128, 128,   0, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128,   0,   0,   0,   0,   0,   0, 
		  0, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128,   0,   0,   0,   0, 128, 
		  0, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128, 128,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
	};
	yych = *p;
	if (yybm[0+yych] & 128) {
		goto yy98;
	}
	++p;
	{ return false; }
yy98:
	++p;
	yych = *p;
	if (yybm[0+yych] & 128) {
		goto yy98;
	}
	{
      out->assign(start, p - start);
      break;
    }
}

  }
  ofs_ = p;
  EatWhitespace();
  return true;
}

bool Lexer::ReadEvalString(EvalString* eval, bool path, string* err) {
  const char* p = ofs_;
  const char* q;
  const char* start;
  for (;;) {
    start = p;
    
{
	unsigned char yych;
	static const unsigned char yybm[] = {
		  0,  16,  16,  16,  16,  16,  16,  16, 
		 16,  16,   0,  16,  16,   0,  16,  16, 
		 16,  16,  16,  16,  16,  16,  16,  16, 
		 16,  16,  16,  16,  16,  16,  16,  16, 
		 32,  16,  16,  16,   0,  16,  16,  16, 
		 16,  16,  16,  16,  16, 208, 144,  16, 
		208, 208, 208, 208, 208, 208, 208, 208, 
		208, 208,   0,  16,  16,  16,  16,  16, 
		 16, 208, 208, 208, 208, 208, 208, 208, 
		208, 208, 208, 208, 208, 208, 208, 208, 
		208, 208, 208, 208, 208, 208, 208, 208, 
		208, 208, 208,  16,  16,  16,  16, 208, 
		 16, 208, 208, 208, 208, 208, 208, 208, 
		208, 208, 208, 208, 208, 208, 208, 208, 
		208, 208, 208, 208, 208, 208, 208, 208, 
		208, 208, 208,  16,   0,  16,  16,  16, 
		 16,  16,  16,  16,  16,  16,  16,  16, 
		 16,  16,  16,  16,  16,  16,  16,  16, 
		 16,  16,  16,  16,  16,  16,  16,  16, 
		 16,  16,  16,  16,  16,  16,  16,  16, 
		 16,  16,  16,  16,  16,  16,  16,  16, 
		 16,  16,  16,  16,  16,  16,  16,  16, 
		 16,  16,  16,  16,  16,  16,  16,  16, 
		 16,  16,  16,  16,  16,  16,  16,  16, 
		 16,  16,  16,  16,  16,  16,  16,  16, 
		 16,  16,  16,  16,  16,  16,  16,  16, 
		 16,  16,  16,  16,  16,  16,  16,  16, 
		 16,  16,  16,  16,  16,  16,  16,  16, 
		 16,  16,  16,  16,  16,  16,  16,  16, 
		 16,  16,  16,  16,  16,  16,  16,  16, 
		 16,  16,  16,  16,  16,  16,  16,  16, 
		 16,  16,  16,  16,  16,  16,  16,  16, 
	};
	yych = *p;
	if (yybm[0+yych] & 16) {
		goto yy105;
	}
	if (yych <= '\r') {
		if (yych <= 0x00) goto yy103;
		if (yych <= '\n') goto yy108;
		goto yy110;
	} else {
		if (yych <= ' ') goto yy108;
		if (yych <= '$') goto yy112;
		goto yy108;
	}
yy103:
	++p;
	{
      last_token_ = start;
      return Error("unexpected EOF", err);
    }
yy105:
	++p;
	yych = *p;
	if (yybm[0+yych] & 16) {
		goto yy105;
	}
	{
      eval->AddText(StringPiece(start, p - start));
      continue;
    }
yy108:
	++p;
	{
      if (path) {
        p = start;
        break;
      } else {
        if (*start == '\n')
          break;
        eval->AddText(StringPiece(start, 1));
        continue;
      }
    }
yy110:
	++p;
	if ((yych = *p) == '\n') goto yy113;
	{
      last_token_ = start;
      return Error(DescribeLastError(), err);
    }
yy112:
	yych = *++p;
	if (yybm[0+yych] & 64) {
		goto yy125;
	}
	if (yych <= ' ') {
		if (yych <= '\f') {
			if (yych == '\n') goto yy117;
			goto yy115;
		} else {
			if (yych <= '\r') goto yy120;
			if (yych <= 0x1F) goto yy115;
			goto yy121;
		}
	} else {
		if (yych <= '/') {
			if (yych == '$') goto yy123;
			goto yy115;
		} else {
			if (yych <= ':') goto yy128;
			if (yych <= '`') goto yy115;
			if (yych <= '{') goto yy130;
			goto yy115;
		}
	}
yy113:
	++p;
	{
      if (path)
        p = start;
      break;
    }
yy115:
	++p;
yy116:
	{
      last_token_ = start;
      return Error("bad $-escape (literal $ must be written as $$)", err);
    }
yy117:
	++p;
	yych = *p;
	if (yybm[0+yych] & 32) {
		goto yy117;
	}
	{
      continue;
    }
yy120:
	yych = *++p;
	if (yych == '\n') goto yy131;
	goto yy116;
yy121:
	++p;
	{
      eval->AddText(StringPiece(" ", 1));
      continue;
    }
yy123:
	++p;
	{
      eval->AddText(StringPiece("$", 1));
      continue;
    }
yy125:
	++p;
	yych = *p;
	if (yybm[0+yych] & 64) {
		goto yy125;
	}
	{
      eval->AddSpecial(StringPiece(start + 1, p - start - 1));
      continue;
    }
yy128:
	++p;
	{
      eval->AddText(StringPiece(":", 1));
      continue;
    }
yy130:
	yych = *(q = ++p);
	if (yybm[0+yych] & 128) {
		goto yy134;
	}
	goto yy116;
yy131:
	++p;
	yych = *p;
	if (yych == ' ') goto yy131;
	{
      continue;
    }
yy134:
	++p;
	yych = *p;
	if (yybm[0+yych] & 128) {
		goto yy134;
	}
	if (yych == '}') goto yy137;
	p = q;
	goto yy116;
yy137:
	++p;
	{
      eval->AddSpecial(StringPiece(start + 2, p - start - 3));
      continue;
    }
}

  }
  last_token_ = start;
  ofs_ = p;
  if (path)
    EatWhitespace();
  // Non-path strings end in newlines, so there's no whitespace to eat.
  return true;
}
