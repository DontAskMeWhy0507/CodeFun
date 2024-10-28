import java.util.List;

public class user {
    private String username;
    private int id;
    private String password;
    private String email;
    private String pathToProfilePicture;
    private List <Book> booksBorrowed;
    private List <String> commentedBooks;
    private List <String> ratedBooks;
    
    public user(String username, int id, String password, String email, String pathToProfilePicture) {
        this.username = username;
        this.id = id;
        this.password = password;
        this.email = email;
        this.pathToProfilePicture = pathToProfilePicture;
    }

    public void profile() {
        // view profile
        // change profile picture
        // change username
        // change email
    }

    // books
    

    public void account() {
        // change password
        // change email
        // change username
        // change profile picture
    }

    public void settings () {
        //  view history books borrowed, books returned, comments, ratings.
        //  change preferences
    }

}
