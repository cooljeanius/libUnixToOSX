/* strchrnul.c
 *
 */

/* Written by Niels Möller <nisse@lysator.liu.se>
 *
 * This file is hereby placed in the public domain.
 */

#if !defined(_RAWMEMCHR_H_) && !defined(strchrnul)
extern char *strchrnul(const char *s, int c_in);
#endif /* !_RAWMEMCHR_H_ && !strchrnul */

/* FIXME: What is this function supposed to do? My guess is that it is
 * like strchr, but returns a pointer to the NUL character, not a NULL
 * pointer, if the character is NOT found. */

char *strchrnul(const char *s, int c)
{
  const char *p = s;
  while (*p && (*p != c)) {
    p++;
  }

  return (char *)p;
}

/* EOF */
