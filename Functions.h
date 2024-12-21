#ifndef FUNCTIONS_H
#define FUNCTIONS_H

class Player_Summary;

long count_words(const string & text);
long get_text_font_word_width(string word);

template <typename T = string>
vector<T*> to_pointers(const vector<T> & vec)
{
  vector<T*> ret;
  for(long i{0}; i < static_cast<long>(vec.size()); ++i)
  {
    ret.push_back(new T{vec[i]});
    ++mem;
  }
  return ret;
}

void crash(const string & message);

template <typename T>
class List
{
  public:
    explicit List(){}
    explicit List(const vector<T*> & t)
    {
      add(t);
    }
    List(const List & obj) = delete;
    List & operator =(const List & obj) = delete;
    T* operator [](const string & name)
    {
      long index{-1};
      for(long i{0}; i < get_list_size(); ++i)
      {
        if(name == m_list[i]->get_name())
        {
          index = i;
        }
      }
      if(index == -1)
      {
        crash("Error: \"" + name + "\" doesn't exist.");
      }
      return m_list[index];
    }
    const T* operator [](const string & name) const
    {
      long index{-1};
      for(long i{0}; i < get_list_size(); ++i)
      {
        if(name == m_list[i]->get_name())
        {
          index = i;
        }
      }
      if(index == -1)
      {
        crash("Error: \"" + name + "\" doesn't exist.");
      }
      return m_list[index];
    }
    T* operator [](const long & index)
    {
      if(index < 0 || index >= get_list_size())
      {
        crash("Error: \"" + to_string(index) + "\" is out of bounds. The size of the list is only " + to_string(get_list_size()) + ".");
      }
      return m_list[index];
    }
    const T* operator [](const long & index) const
    {
      if(index < 0 || index >= get_list_size())
      {
        crash("Error: \"" + to_string(index) + "\" is out of bounds. The size of the list is only " + to_string(get_list_size()) + ".");
      }
      return m_list[index];
    }
    void add(T* t)
    {
      m_list.push_back(t);
    }
    void add(vector<T*> t)
    {
      for(long i{0}; i < get_list_size(); ++i)
      {
        delete m_list[i];
        m_list[i] = nullptr;
        --mem;
      }
      m_list.clear();
      m_list = t;
    }
    void remove(const string & t)
    {
      long i{0};
      while(i < get_list_size() && m_list[i]->get_name() != t)
      {
        ++i;
      }
      if(i == get_list_size())
      {
        crash("Error: \"" + t + "\" is not in the list.");
      }
      delete m_list[i];
      m_list[i] = nullptr;
      --mem;
      m_list.erase(m_list.begin() + i);
    }
    long get_list_size() const
    {
      return m_list.size();
    }
    vector<T*> get_list() const
    {
      return m_list;
    }
    bool is_in_list(const string & t) const
    {
      for(long i{0}; i < get_list_size(); ++i)
      {
        if(t == m_list[i]->get_name())
        {
          return true;
        }
      }
      return false;
    }
    void swap(const string & name1, const string & name2)
    {
      long index1{-1};
      long index2{-1};
      for(long i{0}; i < get_list_size(); ++i)
      {
        if(name1 == m_list[i]->get_name())
        {
          index1 = i;
        }
        if(name2 == m_list[i]->get_name())
        {
          index2 = i;
        }
      }
      if(index1 == -1)
      {
        crash("Error: \"" + name1 + "\" doesn't exist.");
      }
      if(index2 == -1)
      {
        crash("Error: \"" + name2 + "\" doesn't exist.");
      }
      T* temp{m_list[index1]};
      m_list[index1] = m_list[index2];
      m_list[index2] = temp;
    }
    ~List()
    {
      for(long i{0}; i < get_list_size(); ++i)
      {
        delete m_list[i];
        m_list[i] = nullptr;
        --mem;
      }
      m_list.clear();
    }
  private:
    vector<T*> m_list{};
};

template <>
class List<string>
{
  public:
    explicit List(){}
    explicit List(const vector<string*> & t)
    {
      add(t);
    }
    List(const List & obj) = delete;
    List & operator =(const List & obj) = delete;
    string* operator [](const string & name)
    {
      long index{-1};
      for(long i{0}; i < get_list_size(); ++i)
      {
        if(name == *m_list[i])
        {
          index = i;
        }
      }
      if(index == -1)
      {
        crash("Error: \"" + name + "\" doesn't exist.");
      }
      return m_list[index];
    }
    const string* operator [](const string & name) const
    {
      long index{-1};
      for(long i{0}; i < get_list_size(); ++i)
      {
        if(name == *m_list[i])
        {
          index = i;
        }
      }
      if(index == -1)
      {
        crash("Error: \"" + name + "\" doesn't exist.");
      }
      return m_list[index];
    }
    string* operator [](const long & index)
    {
      if(index < 0 || index >= get_list_size())
      {
        crash("Error: \"" + to_string(index) + "\" is out of bounds. The size of the list is only " + to_string(get_list_size()) + ".");
      }
      return m_list[index];
    }
    const string* operator [](const long & index) const
    {
      if(index < 0 || index >= get_list_size())
      {
        crash("Error: \"" + to_string(index) + "\" is out of bounds. The size of the list is only " + to_string(get_list_size()) + ".");
      }
      return m_list[index];
    }
    void add(string* t)
    {
      m_list.push_back(t);
    }
    void add(vector<string*> t)
    {
      for(long i{0}; i < get_list_size(); ++i)
      {
        delete m_list[i];
        m_list[i] = nullptr;
        --mem;
      }
      m_list.clear();
      m_list = t;
    }
    void remove(const string & t)
    {
      long i{0};
      while(i < get_list_size() && *m_list[i] != t)
      {
        ++i;
      }
      if(i == get_list_size())
      {
        crash("Error: \"" + t + "\" is not in the list.");
      }
      delete m_list[i];
      m_list[i] = nullptr;
      --mem;
      m_list.erase(m_list.begin() + i);
    }
    long get_list_size() const
    {
      return m_list.size();
    }
    vector<string*> get_list() const
    {
      return m_list;
    }
    bool is_in_list(const string & t) const
    {
      for(long i{0}; i < get_list_size(); ++i)
      {
        if(t == *m_list[i])
        {
          return true;
        }
      }
      return false;
    }
    void swap(const string & name1, const string & name2)
    {
      long index1{-1};
      long index2{-1};
      for(long i{0}; i < get_list_size(); ++i)
      {
        if(name1 == *m_list[i])
        {
          index1 = i;
        }
        if(name2 == *m_list[i])
        {
          index2 = i;
        }
      }
      if(index1 == -1)
      {
        crash("Error: \"" + name1 + "\" doesn't exist.");
      }
      if(index2 == -1)
      {
        crash("Error: \"" + name2 + "\" doesn't exist.");
      }
      string* temp{m_list[index1]};
      m_list[index1] = m_list[index2];
      m_list[index2] = temp;
    }
    ~List()
    {
      for(long i{0}; i < get_list_size(); ++i)
      {
        delete m_list[i];
        m_list[i] = nullptr;
        --mem;
      }
      m_list.clear();
    }
  private:
    vector<string*> m_list{};
};

#endif
