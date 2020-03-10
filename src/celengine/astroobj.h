#pragma once

#include <string>
#include <unordered_set>
#include <celengine/selection.h>
#include <celengine/parseobject.h>

class UserCategory;

class AstroCatalog
{
 public:
    typedef uint32_t IndexNumber;
    static const IndexNumber InvalidIndex = UINT32_MAX;
};

class AstroObject
{
    AstroCatalog::IndexNumber m_mainIndexNumber { AstroCatalog::InvalidIndex };
public:
    AstroObject() = default;
    AstroObject(AstroObject &);
    AstroObject(AstroObject &&);
    ~AstroObject();

    AstroCatalog::IndexNumber getIndex() const { return m_mainIndexNumber; }
    void setIndex(AstroCatalog::IndexNumber);

//  Common index stuff
 protected:
    static std::unordered_map<AstroCatalog::IndexNumber, AstroObject*> m_mainIndex;
    static void freeIndexNumber(AstroCatalog::IndexNumber i) { m_mainIndex.erase(i); }
    static void assignIndexNumber(AstroCatalog::IndexNumber i, AstroObject *o) { m_mainIndex[i] = 0; }
 public:
    static AstroObject *find(AstroCatalog::IndexNumber);

//  Auto Indexing stuff
    static constexpr AstroCatalog::IndexNumber MaxAutoIndex = UINT32_MAX - 1;
    static AstroCatalog::IndexNumber getNewAutoIndex() { return m_autoIndex--; }
    static AstroCatalog::IndexNumber getCurrentAutoIndex() { return m_autoIndex; }
    static void recoverAutoIndex()
    {
        if (m_autoIndex < MaxAutoIndex)
            ++m_autoIndex;
    }
    AstroCatalog::IndexNumber setNewAutoIndex();
    static void resetAutoIndex(AstroCatalog::IndexNumber i = MaxAutoIndex) { m_autoIndex = i; }
 protected:
    static AstroCatalog::IndexNumber m_autoIndex;

// Category stuff
 public:
    typedef std::unordered_set<UserCategory*> CategorySet;

private:
    CategorySet *m_cats { nullptr };
protected:
    bool _addToCategory(UserCategory*);
    bool _removeFromCategory(UserCategory*);
public:
    virtual Selection toSelection();
    bool addToCategory(UserCategory*);
    bool addToCategory(const std::string&, bool = false, const std::string &domain = "");
    bool removeFromCategory(UserCategory*);
    bool removeFromCategory(const std::string&);
    bool clearCategories();
    bool isInCategory(UserCategory*) const;
    bool isInCategory(const std::string&) const;
    int categoriesCount() const { return m_cats == nullptr ? 0 : m_cats->size(); }
    CategorySet *getCategories() const { return m_cats; };
    bool loadCategories(Hash*, DataDisposition = DataDisposition::Add, const std::string &domain = "");
    friend UserCategory;
};
