// Original: unknown, JP-only text catalog (JP 983 exe)
#ifndef PG_JP983_NEW_JPTEXTCATALOG_H
#define PG_JP983_NEW_JPTEXTCATALOG_H

// The JP text of a KR (Korean) source text, or the key unchanged when the
// catalog has no entry (docs/JP_REFRESH_UI.md, "JP texts"). JP 0xb4eb80:
// key in ecx, plain `ret`, so __fastcall (the /Gr default); the catalog is a
// function-local static built on first use (guard 0xf04310, object
// 0xf041e8). Name ours.
const char* Jp_LookupText(const char* text);   // 0xb4eb80

#endif // PG_JP983_NEW_JPTEXTCATALOG_H
