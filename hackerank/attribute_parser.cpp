#include <bits/stdc++.h>
using namespace std;

const string tag = "tag";
const regex pattern("[.=<> ,\"~]+");

const string test_xml = "<tag1 value = \"HelloWorld\">\n"
                        "<tag2 name = \"Name1\">\n"
                        "</tag2>\n"
                        "</tag1>";

const string test_xml1 = "<tag1 value = \"value\">\n"
                         "<tag2 name = \"name\">\n"
                         "<tag3 another = \"another\" final = \"final\">\n"
                         "</tag3>\n"
                         "</tag2>\n"
                         "</ tag1>\n";
struct Node
{
  string name;
  unordered_map<string, string> data;
  Node *next;
  Node(const string n, const unordered_map<string,
                                           string> &d) : name(n), data(d), next(nullptr) {}
  Node() : name(""), data({}), next(nullptr) {}
};

vector<string> getsplit(const string &text)
{
  sregex_token_iterator iter(text.begin(), text.end(), pattern, -1);
  sregex_token_iterator end;

  // Collect splits
  vector<string> result(iter, end);

  // Remove empty string
  result.erase(remove_if(result.begin(),
                         result.end(), [](const string &s)
                         { return s.empty(); }),
               result.end());
  return result;
}

unordered_map<string, string> getlinetagdata(const vector<string> &data)
{
  if (data.size() < 3) // we expect at lease three element
    return {};
  unordered_map<string, string> mp;
  for (int i = 1; i < data.size(); i += 2)
    mp[data[i]] = data[i + 1];

  return mp;
}

Node *makeNode(const string &text, int nLine)
{
  nLine = nLine / 2;
  int start_pos = 0;
  int end_pos = 0;
  int i = 0;
  Node *h = new Node();
  auto cur = h;
  while ((end_pos = text.find('\n', start_pos)) != string::npos && i++ < nLine)
  {
    string line = text.substr(start_pos, end_pos - start_pos);

    // Get split
    auto split = getsplit(line);
    if (split.empty())
      break;
    auto node = new Node(split[0], getlinetagdata(split));
    cur->next = node;
    cur = cur->next;

    // move to the next line
    ++end_pos;
    start_pos = end_pos;
  }
  return h->next;
}

vector<string> getQueries(const string &xml, int nLine,
                          const vector<string> &queries, int nQueries)
{
  auto head = new Node();
  head->next = makeNode(xml, nLine);
  // printNode(head->next);
  Node *cur = nullptr;
  if (!head) // if xml is malformed or empty
    return {};
  vector<string> result;
  for (int i = 0; i < nQueries; ++i)
  {
    auto split = getsplit(queries[i]);
    if (split.empty())
    {
      // result.push_back("Not Found");
      continue;
    }

    auto lastEle = split[split.size() - 1];
    cur = head;
    bool found = true;
    int j = 0;
    // tag1, value
    for (j; ((j < split.size() - 1) && found && cur); ++j)
    {
      cur = cur->next;
      if (cur->name != split[j])
      {
        result.push_back("Not Found");
        found = false;
        continue;
      }
    }

    found = (cur->data.find(lastEle) != cur->data.end());

    if (found)
      result.push_back(cur->data[lastEle]);
    else
      result.push_back("Not Found");
  }
  // Some cleanup
  delete head;
  head = nullptr;

  return result;
}

int main()
{
  vector<string> queries{
      "tag1.tag2~name.",
      "tag1~name",
      "tag1~value"};

  auto res = getQueries(test_xml, 4, queries, queries.size());
  for (const auto &s : res)
    cout << s << "\n";
  cout << endl;

  queries = {
      "tag1~value",
      "tag1.tag2.tag3~name",
      "tag1.tag2.tag3~final"};

  res = getQueries(test_xml1, 6, queries, queries.size());
  for (const auto &s : res)
    cout << s << "\n";
  cout << endl;

  return 0;
}

void printNode(const Node *node)
{
  auto cur = node;
  while (cur)
  {
    cout << cur->name << ": ";
    auto l = cur->data;
    for (const auto &i : l)
      cout << "key: " << i.first << " val: " << i.second << endl;
    cout << endl;
    cur = cur->next;
  }
}