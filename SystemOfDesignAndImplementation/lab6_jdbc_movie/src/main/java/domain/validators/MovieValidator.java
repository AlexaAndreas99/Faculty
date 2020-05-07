package domain.validators;

import domain.Movie;

public class MovieValidator implements Validator<Movie>{
    @Override
    public void validate(Movie entity) throws ValidatorException {
        if (entity.getName().isEmpty()) {
            throw new ValidatorException("Illegal name given");
        }
        if(entity.getTimesRented()<0)
            throw new ValidatorException("Invalid value given");

    }
}
