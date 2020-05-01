/*
DynamicVector::DynamicVector(int cap)
{
	this->size = 0;
	this->cap = cap;
	this->elems = new Telem[cap];
}

DynamicVector::DynamicVector(const DynamicVector& v)
{
	this->size = v.size;
	this->cap = v.cap;
	this->elems = new Telem[this->cap];
	for (int i = 0; i < this->size; i++)
		this->elems[i] = v.elems[i];
}
DynamicVector::~DynamicVector()
{
	delete[] this->elems;
}

void DynamicVector::add(const Telem &e)
{
	if (this->size == this->cap)
		this->resize();
	this->elems[this->size] = e;
	this->size++;
}


void DynamicVector::resize(double factor)
{
	this->cap *= factor;
	Telem* els = new Telem[this->cap];
	for (int i = 0; i < this->size; i++)
		els[i]=this->elems[i] ;

	delete[] this->elems;
	elems = els;
}
*/