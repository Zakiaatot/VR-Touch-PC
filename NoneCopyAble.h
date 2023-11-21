#ifndef _NONE_COPY_ABLE_H_
#define _NONE_COPY_ABLE_H_
class NoneCopyAble
{
protected:
	NoneCopyAble() {}
	virtual ~NoneCopyAble() {}

private:
	NoneCopyAble(const NoneCopyAble&);
	const NoneCopyAble& operator=(const NoneCopyAble&);
};
#endif //!f_NONE_COPY_ABLE_H_
