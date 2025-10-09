// Filter 14 : Purple Effect
void PurpleEffect(Image& image) {
    for (int y = 0; y < image.height; y++) {
        for (int x = 0; x < image.width; x++) {
            unsigned char r = image(x, y, 0);
            unsigned char g = image(x, y, 1);
            unsigned char b = image(x, y, 2);
            int newR = min(255, (int)(r * 1.5));
            int newG = max(0, (int)(g * 0.5));
            int newB = min(255, (int)(b * 1.5));
            image(x, y, 0) = newR;
            image(x, y, 1) = newG;
            image(x, y, 2) = newB;
        }
    }
    cout << "Purple effect successfully!"<<endl;
}