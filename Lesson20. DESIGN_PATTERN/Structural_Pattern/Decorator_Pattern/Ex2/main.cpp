#include <iostream>
#include <string>

using namespace std;

class Shape
{
    protected:
        string color;

    public:
        Shape(const string &color_ = "black") : color(color_) {} //Constructor khởi tạo màu sắc

        virtual void draw() const
        {
            cout << "Drawing a generic shape" << endl;
        }

        virtual double calculateArea() const
        {
            return 0.0;
        }
};

// Đối tượng được khởi tạo ban dầu
class Circle : public Shape
{
    private:
        double radius;

    public:
        Circle(double r, const string &color_ = "black")//Constructor khởi tạo kích thước và màu sắc
            : radius(r), Shape(color_) {}

        void draw() const override //Ghi đè hàm draw()
        {
            cout << "Drawing a Circle in color " << color << endl;
        }

        double calculateArea() const override //Ghi đè hàm calculateArea()
        {
            return 3.14 * radius * radius;
        }
};


//
class ShapeDecorator : public Shape
{
    protected:
        Shape *decoratedShape; //Con trỏ quản lý đối tượng 

    public:
        ShapeDecorator(Shape *shape) : decoratedShape(shape){} //Truyền đối tượng cần thêm chức năng vào

        virtual void draw() const override
        {
            decoratedShape->draw();
        }

        virtual double calculateArea() const override
        {
            return decoratedShape->calculateArea();
        }
};

//Thêm chức năng vẽ viền
class BorderDecorator : public ShapeDecorator
{
    private:
        double borderWidth;

    public:
        BorderDecorator(Shape *shape, double width)//Truyền vào đối tượng cần thêm chức năng và độ dài viền 
            : ShapeDecorator(shape), borderWidth(width) {}

        void draw() const override
        {
            decoratedShape->draw();//Gọi chức năng gốc của hàm Circle->draw()
            cout << "   with border width of " << borderWidth << endl; //Thêm vào chức năng mới.
        }
};


//Thêm chức năng vẽ bóng
class ShadowDecorator : public ShapeDecorator
{
    private:
        string shadowColor;

    public:
        ShadowDecorator(Shape *shape, const string &color) //Truyền vào đối tượng cần thêm chức năng và màu bóng
            : ShapeDecorator(shape), shadowColor(color) {}

        void draw() const override
        {
            decoratedShape->draw();
            cout << "   with shadow color " << shadowColor << endl; //Thêm chức năng vẽ bóng
        }
};


int main(int argc, char const *argv[])
{
    Shape *shape = new Circle(5, "red");  //shape = 0x01

    shape = new ShadowDecorator(shape, "yellow"); //shape = 0xb2

    /*
        Khi khởi tạo đối tượng Circle, giả sử shape đang quản lý địa chỉ 0x01, chỉ có chức năng vẽ hình và tô màu
        Khi khởi tạo đối tượng ShadowDecorator và truyền vào:
            - Màu sắc bóng shadowColor(color)
            - Địa chỉ của shape = 0x01,  và gọi Constructor ShapeDecorator(shape)
                Bây giờ ta có decoratedShape = shape tức biến  decoratedShape = 0x01
            Nên khi gọi hàm draw() tại 0xb2
                decoratedShape->draw(); //Gọi hàm draw tại địa chỉ 0x01 trước, tức là hàm shape->draw()
                Sau đó gọi thêm hàm chức năng vẽ bóng

        Tức shape bây giờ đang quản lý địa chỉ 0xb2 nhưng con trỏ decoratedShape = 0x01.
    */

    shape = new BorderDecorator(shape, 2);              // 0xc3

    /*
        Khi khởi tạo đối tượng ShadowDecorator và truyền vào:
            - Độ dài borderWidth(width)
            - Địa chỉ của shape = 0xb2 lúc này đã có chức năng vẽ bóng, ShapeDecorator(shape)
                Bây giờ ta có decoratedShape = 0xb2 tức biến decoratedShape = 0xb2
            Nên khi gọi hàm draw()
                decoratedShape->draw(); //Gọi hàm draw tại địa chỉ 0xb2 trước, đã có chức năng vẽ bóng
                trong hàm draw() tại 0xb2 tiếp tục thực hiện một hàm decoratedShape->draw() tại 0x01 là hàm ban đầu
                Sau đó gọi thêm hàm chức năng vẽ viền

        Lúc này ta đã có xếp chồng ba hàm bằng cách, gọi con trỏ 0xc3 -> 0xb2 -> 0x01
    */

    shape->draw();

    cout << "Area: " << shape->calculateArea() << endl;

    delete shape;

    return 0;
}
