#include <iostream>

struct MusicNode
{
  std::string name;
  MusicNode *next;
  MusicNode *prev;
  MusicNode(const std::string &n) : name(n), next(nullptr), prev(nullptr) {};
  MusicNode(const std::string &n, MusicNode *nxt) : name(n), next(nxt), prev(nullptr) {};
  MusicNode(const std::string &n, MusicNode *nxt, MusicNode *prv) : name(n), next(nxt), prev(prv) {};
};

class MP3player
{
  MusicNode *head;    // First song in playlist
  MusicNode *tail;    // Last song in playlist (for appending)
  MusicNode *current; // Currently playing song

public:
  MP3player(const std::string &song_name)
      : head(new MusicNode(song_name)), tail(head), current(head)
  {
  }

  ~MP3player()
  {
    MusicNode *cur = head;
    while (cur)
    {
      MusicNode *next = cur->next;
      delete cur;
      cur = next;
    }
  }

  void QueueSong(const std::string &new_song, const std::string &after = "")
  {
    MusicNode *new_node = new MusicNode(new_song);

    // If playlist is empty (shouldn't happen with constructor)
    if (!head)
    {
      head = tail = current = new_node;
      return;
    }

    // If no 'after' specified or playlist has only one song, append to end
    if (after.empty() || head == tail)
    {
      tail->next = new_node;
      new_node->prev = tail;
      tail = new_node;
      return;
    }

    // Search for the song to insert after
    MusicNode *cur = head;
    while (cur && cur->name != after)
      cur = cur->next;

    // If found, insert after it
    if (cur)
    {
      new_node->next = cur->next;
      new_node->prev = cur;

      if (cur->next)
      {
        cur->next->prev = new_node;
      }
      else
      {
        // Inserting after tail
        tail = new_node;
      }

      cur->next = new_node;
    }
    else
    {
      // Song not found, append to end
      tail->next = new_node;
      new_node->prev = tail;
      tail = new_node;
    }
  }

  void NextSong()
  {
    if (current && current->next)
    {
      current = current->next;
    }
  }

  void PreviousSong()
  {
    if (current && current->prev)
    {
      current = current->prev;
    }
  }

  void PlayCurrent()
  {
    if (current)
    {
      std::cout << "Now playing: " << current->name << std::endl;
    }
  }

  void GetSongList()
  {
    MusicNode *cur = head;
    while (cur)
    {
      std::cout << cur->name;
      if (cur == current)
      {
        std::cout << " [CURRENT]";
      }
      std::cout << std::endl;
      cur = cur->next;
    }
  }
};

int main()
{
  {
    MP3player mp3("WestLife");
    mp3.QueueSong("Backstreet Boys");
    mp3.QueueSong("Marie Carey", "WestLife");
    mp3.QueueSong("Pasuma");
    mp3.GetSongList();
  }

  return 0;
}