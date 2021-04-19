#ifndef R_HUST_OS_DESIGN_UTIL_HPP_
#define R_HUST_OS_DESIGN_UTIL_HPP_ 1

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <atomic>
#include <stdexcept>

inline mode_t get_file_permission(std::string fname) {
    struct stat statbuf;
    auto res = stat(fname.c_str(), &statbuf);
    if(res == -1)
        throw std::runtime_error(std::string("Unable to stat file ") + fname);
    return statbuf.st_mode;
}

// Copied from https://github.com/recolic/hust-os-exp/blob/master/fs_prettyprint.hpp
inline std::string fsizeToString(const size_t fsize) {
    if(fsize < 1024)
        return std::to_string(fsize);
    const auto KiB = (double)fsize / 1024.;
    if(KiB < 1024) return std::to_string(KiB) + "Ki";
    const auto MiB = KiB / 1024.;
    if(MiB < 1024) return std::to_string(MiB) + "Mi";
    const auto GiB = MiB / 1024.;
    if(GiB < 1024) return std::to_string(GiB) + "Gi";
    const auto TiB = GiB / 1024.;
    if(TiB < 1024) return std::to_string(TiB) + "Ti";
    const auto PiB = TiB / 1024.;
    return std::to_string(PiB) + "Pi";
}

#include <gtkmm.h>

class ProcGUI : public Gtk::Window
{
public:
    ProcGUI(std::string title, std::string initTxt)
        : m_txt(initTxt.c_str()), copiedBytes(0), finished(false) {
        set_title(title.c_str());
        set_border_width(10);
        dispatcher.connect(sigc::mem_fun(*this, &ProcGUI::dispatcherHandler));
        add(m_txt);
        m_txt.show();
    }
    virtual ~ProcGUI() {}

    std::atomic<size_t> copiedBytes;
    std::atomic<bool> finished;
    Glib::Dispatcher dispatcher;
protected:
    Gtk::Label m_txt;
    void dispatcherHandler() {
        auto prefix = finished ? "Finished: " : "Copied: ";
        std::string s = std::string() + prefix + fsizeToString(copiedBytes) + "B";
        m_txt.set_text(s.c_str());
    }
};



#endif
