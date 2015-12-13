## Drupal resume

Drupal resume is a Drupal 7 module which by setting up some fields it will give you a bootstrappy, mobile friendly, nice design Curriculum Vitae (CV) page. You can see my [CV](http://www.papasavvas.me/), which is build using this module.

## Motivation

I started re-developing my site and I wanted to create a catchy design CV page. However, as a developer, I didn't want to setup a page and put some raw content there. I wanted to create something that I will CRUD (Create, Read, Update , Delete) and to be flexible and convenient -  a phrase I use all the time :) .

So, I started creating this module. I added the sections I wanted but I needed them to be flexible so in the future I can add hooks and add more sections easily. I used my knowledge from Zend MVC Framework and along with Drupal 7 APIs, I came with up this module.

I am using it as a sub-module so I can update it easily from my GitHub page and don't have to worry of copy/pasting files.

## Requirements

The module requires some essential components to work:

* [Twitter Bootstrap 3](http://getbootstrap.com/) or you can use the [Boostrap module](https://www.drupal.org/project/bootstrap) which is the one I use in my website
* [Font Awesome](https://fortawesome.github.io/Font-Awesome/icons/) 

## Installation

### 1. Add this module with the Drupal classic way

* Download the zip file of this repo
* Add it to your `sites/all/modules` folder
* Go to `admin/modules` url and install the module
* You will find the module settings under `admin/structure/resume`
* A page will be created which the url is listed inside the resume settings.

### 1. Add this module as a submodule (Assuming you are using version control for your Drupal website)

* Navigate first to your root folder of your Drupal website - where the index.php, cron.php etc files exist
* Execute this command to add this Drupal module as a submodule for your site `git submodule add https://github.com/poupouxios/drupal-resume.git sites/all/modules/resume`
* Then execute `git submodule init` and `git submodule update`. This will fetch the module and add it in the folder you specified
* The rest of the steps are the same like above ( From Go to.. step and after)

## License

This project is licensed under the MIT open source license.

## About the Author

[Valentinos Papasavvas](http://www.papasavvas.me/) works as a Senior Web Developer and iOS Developer in a company based in Sheffield/UK. You can find more on his [website](http://www.papasavvas.me/).
