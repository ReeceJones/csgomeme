#pragma once
#include <Windows.h>
#include "IMaterial.h"
#include "Drawing.h"

struct FileHandle_t;
class KeyValues
{
public:
	static void SetUseGrowableStringTable(bool bUseGrowableTable);

	KeyValues(const char *setName) {}

	class AutoDelete
	{
	public:
		explicit inline AutoDelete(KeyValues *pKeyValues) : m_pKeyValues(pKeyValues) {}
		explicit inline AutoDelete(const char *pchKVName) : m_pKeyValues(new KeyValues(pchKVName)) {}
		inline ~AutoDelete(void) { if (m_pKeyValues) m_pKeyValues->deleteThis(); }
		inline void Assign(KeyValues *pKeyValues) { m_pKeyValues = pKeyValues; }
		KeyValues *operator->() { return m_pKeyValues; }
		operator KeyValues *() { return m_pKeyValues; }
	private:
		AutoDelete(AutoDelete const &x); 		AutoDelete & operator= (AutoDelete const &x); 		KeyValues *m_pKeyValues;
	};

	KeyValues(const char *setName, const char *firstKey, const char *firstValue);
	KeyValues(const char *setName, const char *firstKey, const wchar_t *firstValue);
	KeyValues(const char *setName, const char *firstKey, int firstValue);
	KeyValues(const char *setName, const char *firstKey, const char *firstValue, const char *secondKey, const char *secondValue);
	KeyValues(const char *setName, const char *firstKey, int firstValue, const char *secondKey, int secondValue);

	const char *GetName() const;
	void SetName(const char *setName);

	int GetNameSymbol() const { return m_iKeyName; }

	void UsesEscapeSequences(bool state); 	void UsesConditionals(bool state); 	bool LoadFromFile(void *filesystem, const char *resourceName, const char *pathID = NULL);
	bool SaveToFile(void *filesystem, const char *resourceName, const char *pathID = NULL, bool sortKeys = false, bool bAllowEmptyString = false);

	bool LoadFromBuffer(char const *resourceName, const char *pBuffer, void* pFileSystem = NULL, const char *pPathID = NULL);

	bool LoadFromBuffer(char const *resourceName, void*buf, void* pFileSystem = NULL, const char *pPathID = NULL);

	KeyValues *FindKey(const char *keyName, bool bCreate = false);
	KeyValues *FindKey(int keySymbol) const;
	KeyValues *CreateNewKey();			void AddSubKey(KeyValues *pSubkey);		void RemoveSubKey(KeyValues *subKey);
	KeyValues *GetFirstSubKey() { return m_pSub; }		KeyValues *GetNextKey() { return m_pPeer; }			void SetNextKey(KeyValues * pDat);
	KeyValues *FindLastSubKey();
	KeyValues* GetFirstTrueSubKey();
	KeyValues* GetNextTrueSubKey();

	KeyValues* GetFirstValue();		KeyValues* GetNextValue();


	int   GetInt(const char *keyName = NULL, int defaultValue = 0);
	uint64 GetUint64(const char *keyName = NULL, uint64 defaultValue = 0);
	float GetFloat(const char *keyName = NULL, float defaultValue = 0.0f);
	const char *GetString(const char *keyName = NULL, const char *defaultValue = "");
	const wchar_t *GetWString(const char *keyName = NULL, const wchar_t *defaultValue = L"");
	void *GetPtr(const char *keyName = NULL, void *defaultValue = (void*)0);
	bool GetBool(const char *keyName = NULL, bool defaultValue = false);
	Color GetColor(const char *keyName = NULL);
	bool  IsEmpty(const char *keyName = NULL);

	int   GetInt(int keySymbol, int defaultValue = 0);
	float GetFloat(int keySymbol, float defaultValue = 0.0f);
	const char *GetString(int keySymbol, const char *defaultValue = "");
	const wchar_t *GetWString(int keySymbol, const wchar_t *defaultValue = L"");
	void *GetPtr(int keySymbol, void *defaultValue = (void*)0);
	Color GetColor(int keySymbol);
	bool  IsEmpty(int keySymbol);

	void SetWString(const char *keyName, const wchar_t *value);
	void SetString(const char *keyName, const char *value);
	void SetInt(const char *keyName, int value);
	void SetUint64(const char *keyName, uint64 value);
	void SetFloat(const char *keyName, float value);
	void SetPtr(const char *keyName, void *value);
	void SetColor(const char *keyName, Color value);
	void SetBool(const char *keyName, bool value) { SetInt(keyName, value ? 1 : 0); }

	void ChainKeyValue(KeyValues* pChain);

	void RecursiveSaveToFile(void* buf, int indentLevel, bool sortKeys = false, bool bAllowEmptyString = false);

	bool WriteAsBinary(void*buffer);
	bool ReadAsBinary(void*buffer, int nStackDepth = 0);

	KeyValues *MakeCopy(void) const;

	void CopySubkeys(KeyValues *pParent) const;

	void Clear(void);

	enum types_t
	{
		TYPE_NONE = 0,
		TYPE_STRING,
		TYPE_INT,
		TYPE_FLOAT,
		TYPE_PTR,
		TYPE_WSTRING,
		TYPE_COLOR,
		TYPE_UINT64,
		TYPE_NUMTYPES,
	};
	types_t GetDataType(const char *keyName = NULL);

	void deleteThis();

	void SetStringValue(char const *strValue);

	void UnpackIntoStructure(struct KeyValuesUnpackStructure const *pUnpackTable, void *pDest, size_t DestSizeInBytes);

	bool ProcessResolutionKeys(const char *pResString);

	bool Dump(class IKeyValuesDumpContext *pDump, int nIndentLevel = 0);

	void RecursiveMergeKeyValues(KeyValues *baseKV);

private:
	KeyValues(KeyValues&);
	~KeyValues();

	KeyValues* CreateKey(const char *keyName);

	KeyValues* CreateKeyUsingKnownLastChild(const char *keyName, KeyValues *pLastChild);
	void AddSubkeyUsingKnownLastChild(KeyValues *pSubKey, KeyValues *pLastChild);

	void RecursiveCopyKeyValues(KeyValues& src);
	void RemoveEverything();

	void RecursiveSaveToFile(void *filesystem, FileHandle_t f, void *pBuf, int indentLevel, bool sortKeys, bool bAllowEmptyString);
	void SaveKeyToFile(KeyValues *dat, void *filesystem, FileHandle_t f, void *pBuf, int indentLevel, bool sortKeys, bool bAllowEmptyString);
	void WriteConvertedString(void *filesystem, FileHandle_t f, void *pBuf, const char *pszString);

	void RecursiveLoadFromBuffer(char const *resourceName, void*buf);

	void AppendIncludedKeys(void* includedKeys);
	void ParseIncludedKeys(char const *resourceName, const char *filetoinclude,
		void* pFileSystem, const char *pPathID, void* includedKeys);

	void MergeBaseKeys(void* baseKeys);

	void InternalWrite(void *filesystem, FileHandle_t f, void *pBuf, const void *pData, int len);

	void Init();
	const char * ReadToken(void*buf, bool &wasQuoted, bool &wasConditional);
	void WriteIndents(void *filesystem, FileHandle_t f, void *pBuf, int indentLevel);

	void FreeAllocatedValue();
	void AllocateValueBlock(int size);

	int m_iKeyName;
	char *m_sValue;
	wchar_t *m_wsValue;

	union
	{
		int m_iValue;
		float m_flValue;
		void *m_pValue;
		unsigned char m_Color[4];
	};

	char	   m_iDataType;
	char	   m_bHasEscapeSequences; 	char	   m_bEvaluateConditionals; 	char	   unused[1];

	KeyValues *m_pPeer;		KeyValues *m_pSub;		KeyValues *m_pChain;
private:
	static int(*s_pfGetSymbolForString)(const char *name, bool bCreate);
	static const char *(*s_pfGetStringForSymbol)(int symbol);
	static void *s_pGrowableStringTable;

public:
	static int GetSymbolForStringClassic(const char *name, bool bCreate = true);
	static const char *GetStringForSymbolClassic(int symbol);

	static int GetSymbolForStringGrowable(const char *name, bool bCreate = true);
	static const char *GetStringForSymbolGrowable(int symbol);

	static int CallGetSymbolForString(const char *name, bool bCreate = true) { return s_pfGetSymbolForString(name, bCreate); }
	static const char *CallGetStringForSymbol(int symbol) { return s_pfGetStringForSymbol(symbol); }
};
