#include <iostream>

struct Member {
    Member() {
        std::cout << "Member constructed at : " << this << "\n";
    }
    ~Member() {
        std::cout << "Member destructed from : " << this << "\n";
    }
    Member(const Member&) { std::cout << "Member is copy constructed at : " << this << "\n"; }
    Member(Member&&) noexcept { std::cout << "Member is move constructed at : " << this << "\n"; }
    Member& operator= (const Member&) { std::cout << "Member is copy assigned\n";  return *this;}
    Member& operator= (Member&&) noexcept { std::cout << "Member is move assigned\n";  return *this;}
    void printAddr() { std::cout << "Member is constructed at : " << this << "\n"; }
};

class Widget {
public:
    Widget() : mm{} {
        std::cout << "Widget constructed at : " << this << "\n";
    }

    ~Widget()  {
        std::cout << "Widget destructed from : " << this << "\n";
    }

    Member& getMemberRef() { return mm; }
    Member getMember() {return mm;}

private:
    Member mm;
};


Widget makeWidget() {
    return Widget{};
}

int main() {

    std::cout << "\n\nmain[0]\n\n";

    {
        std::cout << "Start of inner scope[0]\n";
        auto&& mref = makeWidget().getMemberRef();
        std::cout << "End of inner scope[0]\n";
        mref.printAddr();
    }

    std::cout << "\n\nmain[1]\n\n";

    {
        std::cout << "Start of inner scope[1]\n";
        auto&& mref = makeWidget().getMember();
        std::cout << "End of inner scope[1]\n";
        mref.printAddr();
    }

    std::cout << "\n\nmain[2]\n\n";

    return EXIT_SUCCESS;
}