void sgl_manager::push(int val)
{
    test.push_back(val);
}

void sgl_manager::read()
{
    for(int i = 0; i < test.size(); i++)
    {
        std::cout << test[i] << std::endl;
    }
}