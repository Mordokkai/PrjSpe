/**
 * Javascript for Design Spark Theme
 */

 /* Same Height Columns */
$.fn.setAllToMaxHeight = function () {
	return this.height(Math.max.apply(this, $.map(this, function (e) { return $(e).height(); })));
}; 

function stickFooter() {
	$('#main').css('padding-bottom', $('#footer').height());
	$('#footer').css('margin-top', -($('#footer').height()));
}

/* Get the browser in scope for IE fixes */
var ie =  ($.browser.msie);
var ie6 = (ie && parseInt($.browser.version, 10) == 6);
var ie7 = (ie && parseInt($.browser.version, 10) == 7);
var ie8 = (ie && parseInt($.browser.version, 10) == 8);

// fix for lack of ie indexOf
	if (!Array.prototype.indexOf){
			Array.prototype.indexOf = function(obj, start) {
	     for (var i = (start || 0), j = this.length; i < j; i++) {
	         if (this[i] === obj) { return i; }
	     }
	     return -1;
		}
	}

// apply checked to the selected element
function setAsChecked() {
	if (/\/nodes\/term\/type/.test(window.location)) {
		$.each(["blog","user","discuss","tool","knowledge","review","partner"], function(num,opt){
			if (window.location.pathname.indexOf(opt) != -1) {
				$('#rb-' + opt, '.jq-explorer').attr('checked','checked');
				return false;
			}
		});
	};
}

// for fancybox - don't know if this needs to be seperate
function set_image_upload_type(type){
   $('#image_upload_type').val(type); 
}

$(document).ready(
	function() {
		if (ie6)
			$.cachedScript("/js/libs/ie7/ie7.js")
		
		if(!ie6)		
			stickFooter();

		if (ie){
			$('li:first-child').addClass('first-child');
			$('li:last-child').addClass('last-child');
		}

		/* for content explorer  */
		// find the locale with javascript only
		
		var site_path = location.pathname.slice(site_base_path.length,location.pathname.length);			
		var path = site_path.split('/');


		/* MOBILE
		-----------------------------*/
		var mobile = false;

		function doMobile(){
			var locale = path[1]==''?'eng':path[1];
			
			var translate = {
				'MyAccount': {'eng': 'My Account', 'chn':'帐户', 'jpn':'アカウント', 'deu':'Mein Konto'},
				'Language':  {'eng': 'Language',   'chn':'语言', 'jpn':'言語',    'deu':'Sprache'},
				'Menu':      {'eng': 'Menu',       'chn':'菜单', 'jpn':'メニュー',   'deu':'Menü'}
			};

			var my_account_translated = translate['MyAccount'][locale];
			var language_translated = translate['Language'][locale];
			var menu_translated = translate['Menu'][locale];

			mobile = true;
			$('#nav, #searchform').appendTo('#toolbar > div');

			$('#profile a').addClass('jq-profile-link').appendTo('#login');
			$('#profile').detach();

			if ( $('#mobile-nav').length <= 0 ) {
				$('#toolbar').prepend('<nav id="mobile-nav"><a class="jq-account" href="#">'+my_account_translated+'</a><a class="jq-language" href="#">'+language_translated+'</a><a class="jq-search" href="#">Search</a><a class="jq-navigation" href="#">'+menu_translated+'</a></nav>');
			}

			if ( $('#main > header .sub-section-title button').length <= 0 ) {
				$('#main > header .sub-section-title').append('<button class="jq-mobile-explorer button small">Filter</button>');
			}

			$('#toolbar .ir').appendTo($('#header > div'));
		}
		
		function undoMobile(){
			mobile = false;
			$('#header > div > hgroup').after($('#searchform'));
			$('#nav').prependTo('#sidebar');
			$('#header > div .ir').appendTo('#toolbar p');

			if ( $('#profile').length <= 0 ) {
				$('#login').after('<nav id="profile"></a>');
			}
			$('#login .jq-profile-link').appendTo('#profile');
			
			$('#searchform, #language, #nav, #login').removeAttr('style');
			
			if ( $('#mobile-nav').length > 0 ) {
				$('#mobile-nav').detach();
			}
					
			if ( $('#main > header .sub-section-title button').length > 0 ) {
				$('#main > header .sub-section-title button').detach();
			}
		}
		
		// Killer function to handle toggling appropriate stuff with the mobile navigation. Smugface -> :) Owen Wilson -> :~)
		function mobileNavToggle(clicked, shown) {
			$('#mobile-nav a').not(clicked).removeClass('active');
			$('#nav, #login, #language, #searchform').not(shown).each(function() {
				if($(this).is(':visible'))
					$(this).slideUp('fast');
			}).promise().done( function(){ 
				clicked.toggleClass('active');
				shown.slideToggle('fast');
			});
			return false;
		}

		//add fancybox to the public side
		$('#add_main_image').fancybox(); // eTs 25/09/12: Who added this? It's halfway through all the mobile JS, it's not using a jq- class, it's not checking the plugin exists, and it doesn't have any options...  2/10 See me!
		
		$('.jq-search').live( 'click', function() {
			mobileNavToggle($(this), $('#searchform'));
		});
		
		$('.jq-navigation').live( 'click', function() {
			mobileNavToggle($(this), $('#nav'));
		});
		
		$('.jq-language').live( 'click', function() {
			mobileNavToggle($(this), $('#language'));
		});
		
		$('.jq-account').live( 'click', function() {
			mobileNavToggle($(this), $('#login'));
		});
		
		$('.jq-mobile-explorer').live( 'click', function() {
			$(this).toggleClass('active');
			$('#explorer').slideToggle('fast');
			return false;
		});

		function getWidth(){ 

			var width = Math.max( $(window).innerWidth(), window.innerWidth ); 
		
			if ($.browser.webkit) {			
				return (width-17);
			} else {
				return width;
			}
		}	

		if (getWidth() < 991) {
			doMobile();
		}

		$(window).resize(function () {
			if (getWidth() < 991)
				doMobile();
			else
				undoMobile();
	    });

		/* END OF MOBILE
		-----------------------------*/
		
		/* MAIN NAVIGATION
		-----------------------------*/
		function createNavigation() {
			$('.jq-nav ul ul').prepend('<span class="jq-close">Close</span>');
			
			$('.jq-nav > ul > li:has(ul)').addClass('jq-subnav');	
			
			$('.jq-close').click(
				function(){
					$('.jq-subnav').removeClass('active');
					$('.jq-subnav > ul').fadeOut('fast');
				}
			);
			
			$('.jq-subnav > a').click(
				function(e) {
					e.preventDefault();
					if(mobile){
						$(this).parent('li').siblings('.jq-subnav').removeClass('active').children('ul').slideUp('fast');
						$(this).siblings('ul').slideToggle('fast');
					} else {
						$(this).parent('li').siblings('.jq-subnav').removeClass('active').children('ul').fadeOut('fast');
						$(this).siblings('ul').fadeToggle('fast');
					}
					$(this).parent('li').toggleClass('active');
				}
			);
		}
		
		/* END OF MAIN NAVIGATION
		-----------------------------*/	

		/* INITIALISE PLUGINS
		-----------------------------*/
		
		/* Tabs */
		if($.fn.tabs){
			$(".jq-tabs").tabs(".jq-panes > section", {effect: 'fade'});
		}
		
		/* Search Tabs */
		if($.fn.tabs){
			var selectedTab = 0;
			if(document.location.search == '?t=tools') { selectedTab = 3;}
			$(".jq-search-tabs").tabs(".jq-search-panes > section", { initialIndex: selectedTab } );
		}
	
		/* Fit Videos */
		if($.fn.fitVids){
			$("#content").fitVids();
		}

		/* END INITIALISE PLUGINS
		-----------------------------*/
		
		languages=['eng','chn','jpn','deu'];

		found_in_url = false;
		for (sub_path_index in path) {
			if (languages.indexOf(path[sub_path_index])!=-1) {
				user_language = path[sub_path_index];
				found_in_url = true;
			}
		}

		if (!found_in_url) {
			if (typeof user_language != 'undefined') {
				forum_languages=[];
				forum_languages['en']='eng';
				forum_languages['zh']='chn';
				forum_languages['ja']='jpn';
				forum_languages['de']='deu';

				user_language = forum_languages[user_language];
			} else {
				user_language = 'eng';
			}
		}

		// this is for loading menu in forum 
		//TODO: This breaks in ie 8 and below	
		
			createNavigation();
		

		// removed ajax loading of content explorer now doing through an include to fix ie6 bug 
//alert(site_base_path+'/ajax/content_finder.php?language='+user_language+'&type=content_explorer&base_path='+site_base_path);	
	
		$.get(site_base_path+'/ajax/content_finder.php?language='+user_language+'&type=content_explorer&base_path='+site_base_path, 
			function(data) {
				// see include in default.ctp
				$('.jq-explorer').html(data);

				$('.jq-explorer li:has(ul)').addClass('children').append('<button class="jq-explorer-trigger">Expand/Collapse</button>');

				$('.jq-explorer-trigger').click(
					function(){
						$(this).parent('li').toggleClass('open');
						$(this).siblings('ul').slideToggle('fast');
					}
				);

				$('.jq-enterer li:has(ul)').addClass('children').append('<button class="jq-enterer-trigger">Expand/Collapse</button>');
				
				$('.jq-enterer-trigger').click(
					function(e){
						
						e.preventDefault();
						$(this).parent('li').toggleClass('open');
						$(this).siblings('ul').slideToggle('fast');
					}
				);
		
				// mapping for paths
				var content_explorer_path_map = {
					'blog':'/nodes/term/type:blog/id:',
					'user':'/users/with_the_same_interests/',
					'discuss':'/nodes/contentexplorerresults/',
					'tool':'/nodes/term/type:tool/id:',
					'knowledge':'/nodes/term/type:knowledge-item/id:',
					'review':'/nodes/term/type:review/id:',
					'partner':'/users/partners_by_specialism/'
				};

				var plural_property = type_property = '';

				//defaults
				$('#rb-blog').click(); 
				var content_explorer_path = 'blog';
				var	content_explorer_selected_type = 'blog';

				for (property in content_explorer_path_map) {
					//FIXME this is a fairly vague routing check !
					plural_property = property + 's'; type_property = 'type:' + property;

					//TODO: This breaks in ie 8 and below	
					if (path.indexOf(property) != -1  || path.indexOf(plural_property) != -1  || path.indexOf(type_property) != -1){
						$('#rb-'+property).click(); 
					}
				}

				// action for content explorer links based on radio button selection
				$('input[id^="rb"]').click(
					function(e) {					
						content_explorer_selected_type = $("input:checked").attr('id').substring(3);
						content_explorer_path_output = content_explorer_path_map[content_explorer_selected_type];	
						get_counts('/'+ content_explorer_selected_type, user_language);
					}
				);

				//do the same thing on page load
				var content_explorer_count_path = $("input:checked").attr('id');		   
				get_counts('/'+ content_explorer_count_path.substring(3), user_language);
				
				$('.jq-explorer li a').click(
					function(e) {
						content_explorer_selected_type = $("input:checked").attr('id').substring(3);
						e.preventDefault();	
						var id = $(this)[0]['id'].substr(5,5);
						content_explorer_path_output = site_base_path+content_explorer_path_map[content_explorer_selected_type];
						window.location =  content_explorer_path_output + id;
						// FIXME this ignores locale in the path
					}
				);

				setAsChecked();

			}
		); 

	    $('#FilterIndexForm').submit(
	    	function() {
		        var filter = '';
		        
		        // job
		        if ($('#FilterJobTitleNo').val() != '') {
		            filter += 'job_title_no:' + $('#FilterJobTitleNo').val() + ';';
		        }

		        // country
		        if ($('#FilterCountry').val() != '') {
		            filter += 'country:' + $('#FilterCountry').val() + ';';
		        }

		         // country
		        if ($('#FilterQ').val() != '') {
		            filter += 'search:' + $('#FilterQ').val() + ';';
		        }

		       var loadUrl =  site_base_path+'/users/index/';
		        if (filter != '') {
		            loadUrl += 'filter:' + filter;
		        }
		        
		        window.location = loadUrl;
		        return false;
	    	}
	    );

	}
); // document ready

function get_counts(typecount, language){
	// get the numbers for the content explorer term occurences via ajax

	$.getJSON(site_base_path+'/terms/content_finder_count'+typecount+'/'+language, function(data) {
		$('.jq-explorer li b').detach(); // get rid of other counts
		$('.jq-explorer li a').each(function(index) {
			var id = $(this)[0]['id'].substr(5,5);
			var count = 0;
		
			if (data != undefined && data[id] != undefined){
				count = data[id];
				
			} else{
				$(this).attr('href','#');
			//	TODO action for nodes with no associated articles
			}
			var elem = this;
			$(this).after(' <b>('+count+')</b>');		
		});
	});
}

function makeSafeID(str){
    return str.replace(/[^0-9a-zA-Z_-]+/g, '');
}

// only for FORUM would prefer to load only in the forum 
// for adding the autogenerated tags found in the excerpt text by the method at /terms/get_terms/

$('#find_terms').click(

	function(){ 
        var no_of_term_selects = 3; // FIXME remove ?- this is not being used methinks sjb

        if ($('.mceEditor').length>0){
        	var instanceID = $('.mceEditor').prev().attr('id');
        	var data = $('#' + instanceID + '_ifr').contents().find("body#tinymce").text();
        } else {
        	var data = $('#message').val();
        }

        if (data.length < 50){
        	$('#tags_container').html('<p>You need to write more for our term analysis system to find suitable tags for the content. Please click the checkboxes from the list below for tags that are suitable for the content you have written.</p>');
        } else {
			$('#tags_container').html('<img src="/img/ajax/circle_ball.gif" width="16" height="16" alt="Loading" /> Finding tags');
			$.ajax({
				url:site_base_path + '/terms/get_terms/',
				dataType:'json',
				data:{language:user_language, text:encodeURIComponent(data)},
				type:'get',
				success: 
					function (results) {
						$('#tags_container').html('<p>n/a</p>');
						ok = false;
						for (result_key in results) {
							if (result_key!='terms_from_yql') {
								if (!ok) {
									$('#tags_container').empty();
								}
								ok = true;

								var this_result = results[result_key];
								var sluggy = makeSafeID(this_result.slug);

								var html = '';
								html += '<span class="tag_box" id="'+ sluggy +'"> ';
								html += this_result.title + '<span class="tag_close"> x </span>';
								html += '<input type="hidden" name="term['+result_key+']" value="'+sluggy+'">';
								html += '</span> ';
								$('#tags_container').append(html);

console.log( $('#'+sluggy + ' input[type:checkbox]').html());


										

                                $('#'+sluggy+ ' span').click(function(sluggy){
                                    $(this).parent().detach();
                                });


							}
						}
				    },
				timeout: 10000,
				error: 
					function (jqXHR, status, errorThrown) {
						$('#tags_container').html('<p>No suitable terms have been found so far, please click the checkboxes from the list below for tags that are suitable to the content you have written</p>');
					}
			});
		}
    }
);


// function to allow for caching of the ie7 / ie6 script
jQuery.cachedScript = function(url, options) {

	// allow user to set any option except for dataType, cache, and url
	options = $.extend(options || {}, {
		dataType: "script",
		cache: true,
		url: url
	});

	// Use $.ajax() since it is more flexible than $.getScript
	// Return the jqXHR object so we can chain callbacks
	return jQuery.ajax(options);
};


// for GA functions MOVED 15-10-14

var elements = document.getElementsByTagName("a");
var pcbQuoteButton = document.getElementsByName("data[QuoteRequest][next]")[0];

if (pcbQuoteButton != undefined){
  pcbQuoteButton.onclick = function  (click) {              
             ga ('set', 'dimension6', 'PCB Quote request');
             ga('send', 'event','link','click', 'PCB Quote request');
                        
         //    return false;  //stopping action - for debug
           }
}


// CAN'T BE IDENTIFIED BY HREF  ['PCB Quote request','/like/'],



/*var action_urls = [['Like','/likes/add'],
                  ['Comment','/comment.php'],
                  ['Reply','/posting.php?mode=reply'],
                  ['DS Mech Download','http://eda.designspark.com/receiver/dsm_dl.php'],
                  ['DS PCB Download','pcb.designspark.info'],
                 
                  ['Modelsource Download','eda_collection_manager/Download'],
                  ['Create a Blog','nodes/blog_add'],
                  ['Forum Post','/posting.php?mode=post'],
                  ['Upload a tool','attachments/tool_add'],
                  ['Write a review','nodes/add_product_review'],
                  ['Upload Knowledge','knowledge-items/add'],
                  ['Clicked a link to RS Online','rs-online.com/web']
                  ];*/
				  
var action_urls = [
				  ['login','/users/login','click'],
				  ['logout','/users/logout','click'],
				  ['myprofile','/users/view','click'],
				  ['comment','/comment.php','click'],
                  ['reply','/posting.php?mode=reply','click'],
                  ['DSM download','http://eda.designspark.com/receiver/dsm_dl.php','download'],
                  ['DSPCB download','pcb.designspark.info','download'],
                 
                  ['modelsource download','eda_collection_manager/Download','download'],
                  ['create a blog','nodes/blog_add','click'],
                  ['forum post','/posting.php?mode=post','click'],
                  ['upload a tool','attachments/tool_add','click'],
                  ['write a review','nodes/add_product_review','click'],
                  ['upload knowledge','knowledge-items/add','click'],
                  ];

 for(var i = 0, len = elements.length; i < len; i++) {
   var link = elements[i];
  
   if (link.attributes.href != undefined){
     var href = link.attributes.href.nodeValue;

//     // we are identifying the actions by the target url, this is probably the most reliable way to track these
// // TODO is this genuinely faster in raw javascript instead of jquery?
       for (var j = action_urls.length - 1; j >= 0; j--) {
  
            if (href.indexOf(action_urls[j][1])  != -1){
            link.action_name = action_urls[j][0];
			link.action_type = action_urls[j][2];
            console.log(link.text);


          link.onclick = function  (click) {  
             
             var link_address = this.attributes.href.nodeValue;
             ga ('set', 'dimension6', this.action_name);
             ga('send', 'event','action',this.action_type, this.action_name);
                      
           //  return false;  //stopping action - for debug
           }
         } 

      };


  }
 }


 var current_location = new String(document.location);
   //  sending the actions associated with the current page - dimension6 based on the current url 

   // TO DO convert this to using a json array for mapping - rather repetitive code

    //register links
    if (current_location.indexOf('/register')  != -1) {                
          ga ('set', 'dimension6', 'register');                    
       }
    
     // login - this means that we are counting going to the login page here not logins per se
    if (current_location.indexOf('login')  != -1) {                
          ga ('set', 'dimension6', 'login');        
    }

    // like links - this means that we are counting unsuccesful likes here
    if (current_location.indexOf('likes/add')  != -1) {                
          ga ('set', 'dimension6', 'like');    
    }

    // comment links - this means that we are counting comments beofre they are entered
    if (current_location.indexOf('comment.php')  != -1) {           
          ga ('set', 'dimension6', 'comment');
    }

    
     // download links - this means that we are counting downloads beofre they are entered and also this is a bit of a vague url match
    if (current_location.indexOf('uploads')  != -1) {                 
          ga ('set', 'dimension6', 'download');       
    }

  // end sending the actions - dimension6 based on the current url

  // this is the successful arrival on the page that confirms activation - this is I think going to be a duplication of the pageview of the same thing - not sure if we need this
   
  
    if (current_location.indexOf('/activation/get_new')  != -1) {   
                 
          ga ('set', 'dimension11', 'activation');
          ga('send', 'event','action','activation','dspcb');               
    }


// we are always sending the pageview at the end here after attaching all the ga dimension properties that we need
ga('send', 'pageview');

