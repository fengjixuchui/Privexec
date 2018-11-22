////

#ifndef PRIVEXEC_APP_HPP
#define PRIVEXEC_APP_HPP
#ifndef _WINDOWS_
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN //
#endif
#include <Windows.h>
#endif
#include <Windowsx.h>
#include <vector>
#include <unordered_map>

namespace priv {

using wid_t = WELL_KNOWN_SID_TYPE;
using alias_t = std::unordered_map<std::wstring, std::wstring>;
bool AppAliasInitialize(HWND hbox, priv::alias_t &alias);

struct Appbox {
  Appbox &operator=(HWND hc) {
    hBox = hc;
    return *this;
  }
  int Index() const {
    // get current appbox index.
    return SendMessage(hBox, CB_GETCURSEL, 0, 0);
  }
  size_t Append(int al, const wchar_t *text, bool sel = false) {
    auto rl = ::SendMessageW(hBox, CB_INSERTSTRING, 1, (LPARAM)text);
    if (rl == CB_ERR || rl == CB_ERRSPACE) {
      return als.size();
    }
    if (sel) {
      ::SendMessageW(hBox, CB_SETCURSEL, (WPARAM)als.size(), 0);
    }
    als.push_back(al);
    return als.size();
  }
  bool IsMatch(int al) {
    auto index = Index();
    if (index >= als.size() || index < 0) {
      return false;
    }
    if (als[index] == al) {
      return true;
    }
    return false;
  }
  int AppIndex() const {
    auto index = Index();
    if (index >= als.size() || index < 0) {
      return -1;
    }
    return als[index];
  }
  HWND hBox{nullptr};
  std::vector<int> als;
};

struct Element {
  HWND hInput{nullptr};
  HWND hButton{nullptr};
  void Visible(BOOL v) {
    EnableWindow(hInput, v);
    EnableWindow(hButton, v);
  }
  std::wstring Content() {
    auto l = GetWindowTextLengthW(hInput);
    if (l == 0 || l > PATHCCH_MAX_CCH * 2) {
      return L"";
    }
    std::wstring s(l + 1, L'\0');
    GetWindowTextW(hInput, &s[0], l + 1); //// Null T
    s.resize(l);
    return s;
  }
  void Update(std::wstring text) {
    // update hInput (commbox or edit text)
    ::SetWindowTextW(hInput, text.data());
  }
};

struct AppCapabilities {
  std::unordered_map<HWND, wid_t> vals;
  void Add(HWND hWnd, int id, wid_t wsid) {
    auto h = GetDlgItem(hWnd, id);
    vals.insert(std::pair<HWND, wid_t>(h, wsid));
  }
  void Visible(BOOL visible) {
    for (auto &e : vals) {
      EnableWindow(e.first, visible);
    }
  }
  std::vector<wid_t> Capabilities() {
    std::vector<wid_t> cas;
    for (auto &c : vals) {
      if (Button_GetCheck(c.first) == BST_CHECKED) {
        cas.push_back((wid_t)c.second);
      }
    }
    return cas;
  }
  void Update(const std::vector<wid_t> &cas) {
    for (auto &c : vals) {
      if (std::find(cas.begin(), cas.end(), c.second) != cas.end()) {
        Button_SetCheck(c.first, TRUE);
      } else {
        Button_SetCheck(c.first, FALSE);
      }
    }
  }
};

class App {
public:
  App() = default;
  App(const App &) = delete;
  App &operator=(const App &) = delete;
  static App *GetThisFromHandle(HWND const window) noexcept {
    return reinterpret_cast<App *>(GetWindowLongPtrW(window, GWLP_USERDATA));
  }
  int run(HINSTANCE hInstance);
  static INT_PTR WINAPI WindowProc(HWND hWnd, UINT message, WPARAM wParam,
                                   LPARAM lParam);
  INT_PTR MessageHandler(UINT message, WPARAM wParam, LPARAM lParam);

private:
  bool Initialize(HWND window);
  bool InitializeCapabilities();
  bool SelChanged();
  bool UpdateCapabilities(const std::wstring &file);
  std::wstring ResolveCMD();
  std::wstring ResolveCWD();
  bool AppExecute();
  HINSTANCE hInst{nullptr};
  HWND hWnd{nullptr};
  Appbox box;
  Element cmd;
  Element cwd;
  Element appx;
  // HWND hExecute{nullptr};
  // HWND hExit{nullptr};
  AppCapabilities appcas;
  alias_t alias;
};
} // namespace priv

#endif
