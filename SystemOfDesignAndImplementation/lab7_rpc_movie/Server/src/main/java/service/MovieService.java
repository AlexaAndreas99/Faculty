package service;

import domain.Movie;
import domain.validators.ValidatorException;
import org.xml.sax.SAXException;
import repository.MovieFileRepository;
import repository.Repository;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;
import java.io.IOException;
import java.sql.SQLException;
import java.util.List;
import java.util.NoSuchElementException;
import java.util.Set;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class MovieService {
    private Repository<Long, Movie> movieRepository;

    public MovieService(Repository<Long, Movie> movieRepository) {
        this.movieRepository = movieRepository;
    }

    public void addMovie(Movie movie) throws ValidatorException, ParserConfigurationException, IOException, SAXException, TransformerException, SQLException {
        movieRepository.save(movie);
    }

    public Set<Movie> getAllMovies() throws SQLException {
        Iterable<Movie> movies = movieRepository.findAll();
        return StreamSupport.stream(movies.spliterator(), false).collect(Collectors.toSet());
    }

    public Movie getMovieById(long id)throws NoSuchElementException {
        return movieRepository.findOne(id).get();
    }

    public void updateMovie(Movie newMovie) throws ValidatorException, SQLException {
        movieRepository.update(newMovie);
    }
    public void deleteMovie(long id) throws SQLException {
        movieRepository.delete(id);
    }

    public void saveToXml() throws ParserConfigurationException, TransformerException, SAXException, IOException {
        movieRepository.saveToXml();
    }

    public void loadFromXml() {
        try{
            movieRepository.loadFromXml();
        }
        catch (Exception e){
            e.printStackTrace();
        }
    }

    public List<Movie> getMoviesByName(String name){
        return ((MovieFileRepository)this.movieRepository).getMoviesByName(name);
    }
    public Movie getMostRentedMovie(){
        return ((MovieFileRepository)this.movieRepository).getMostRentedMovie();
    }
}
