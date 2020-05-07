package domain.validators;

import domain.Client;


import java.util.Optional;
import java.util.stream.StreamSupport;

/**
 * @author Sergiu
 */

public class ClientValidator implements Validator<Client> {
    public ClientValidator() {

    }

    @Override
    public void validate(Client entity) throws ValidatorException {
        if (entity.getName().isEmpty() || entity.getName().matches(".*\\d.*")) {
            throw new ValidatorException("Illegal name given");
        }
        if (!entity.getCnp().matches("^[0-9]+$") || entity.getCnp().length() != 13) {
            throw new ValidatorException("Illegal CNP given");
        }
    }
}
