/* generated by po2c 1.0.2 - Do not modify */

#include <stdio.h>
#include <string.h>

static const char * _po2c_msgids[] = {
	NULL
};

struct _po2c_msg {
	int msgid;
	const char * msgstr;
};

static struct {
	const char * lang;
	const char * charset;
	struct _po2c_msg * msgs;
} _po2c_langs[] = {
	{ NULL, NULL, NULL }
};

/* code */

static struct _po2c_msg * _po2c_lang=NULL;
static int _po2c_lang_size=0;
static const char * _po2c_charset=NULL;

void po2c_setlang(const char * lang)
{
	int n;

	_po2c_lang=NULL;
	_po2c_lang_size=0;
	_po2c_charset=NULL;

	/* if lang is NULL or "", deactivate it */
	if(lang == NULL || *lang == '\0')
		return;

	/* searches for a valid language array */
	for(n=0;_po2c_lang == NULL && _po2c_langs[n].lang != NULL;n++)
	{
		if(strcmp(lang, _po2c_langs[n].lang) == 0) {
			_po2c_lang=_po2c_langs[n].msgs;
			_po2c_charset=_po2c_langs[n].charset;
		}
	}

	/* try partial searches */
	for(n=0;_po2c_lang == NULL && _po2c_langs[n].lang != NULL;n++)
	{
		if(strncmp(lang, _po2c_langs[n].lang, 2) == 0) {
			_po2c_lang=_po2c_langs[n].msgs;
			_po2c_charset=_po2c_langs[n].charset;
		}
	}

	/* if found, count entries */
	if(_po2c_lang != NULL)
	{
		struct _po2c_msg * m;

		for(m=_po2c_lang;m->msgid != -1;m++)
			_po2c_lang_size++;
	}
}

const char * po2c_gettext(const char * msgid)
{
	struct _po2c_msg * m;
	int b, t, n, c;

	/* if no language is set or msgid is empty, return msgid as is */
	if(_po2c_lang == NULL || *msgid == '\0')
		return(msgid);

	/* binary-search for the msgid */
	b=0; t=_po2c_lang_size - 1;

	while(t >= b)
	{
		n=(b + t) / 2;
		m=&_po2c_lang[n];

		c=strcmp(msgid, _po2c_msgids[m->msgid]);

		if(c == 0)
			return(m->msgstr);
		else
		if(c < 0)
			t=n - 1;
		else
			b=n + 1;
	}

	return(msgid);
}

const char * po2c_getcharset(void)
{
	if (_po2c_charset)
		return _po2c_charset;
	else
		return "ASCII";
}

int po2c_getnumlangs(void)
{
	int n = 0;
	while (_po2c_langs[n].lang)
		n++;
	
	return n;
}

const char * po2c_getlang(int num)
{
	return _po2c_langs[num].lang;
}
