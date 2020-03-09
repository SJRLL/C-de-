#pragma once
#include "Common.h"

class PageCache
{
public:
	// 
	Span* _NewSpan(size_t numpage);
	Span* NewSpan(size_t numpage);
	void ReleaseSpanToPageCache(Span* span);

	Span* GetIdToSpan(PAGE_ID id);
	static PageCache& GetInstance()
	{
		static PageCache inst;
		return inst;
	}
private:
	PageCache()
	{}
	PageCache(const PageCache&) = delete;
	SpanList _spanLists[MAX_PAGES];
	std::map<PAGE_ID, Span*> _idSpanMap;
	std::mutex _mtx;
};

//static PageCache pageCacheInst;