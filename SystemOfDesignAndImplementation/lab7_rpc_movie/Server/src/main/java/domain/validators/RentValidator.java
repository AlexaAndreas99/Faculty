package domain.validators;

import domain.Rent;

public class RentValidator implements  Validator<Rent> {
    @Override
    public void validate(Rent entity) throws ValidatorException {
        if(entity.getMovieRentedId()<0 || entity.getRentedToClientId()<0)
            throw new ValidatorException("Invalid value given!");
        if(entity.getStartDate().length()!=10)//xx.xx.xxxx
            throw  new ValidatorException("Invalid date!");
    }
}
