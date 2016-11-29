/**
 * Contains javascript to display popups.
 *
 * @file av_popup.js
 */

(function ($) {
  Drupal.behaviors.avPopup = {
    attach: function (context, settings) {
      var avPopup = Drupal.settings.avPopup;

      // Remove cookie conform settings.
      if (avPopup.reset) {
        $.cookie("av_popup", null, {path: '/'});
      }

      var $cookie = $.cookie("av_popup");
      if (!$cookie || avPopup.reset) {
        setTimeout(function () {
          $.magnificPopup.open({
            key: 'av-popup',
            showCloseBtn: false,
            enableEscapeKey: false,
            closeOnBgClick: false,
            closeOnContentClick: false,
            items: {},
            type: 'inline',
            inline: {
              markup: avPopup.markup
            },
            callbacks: {
              open: function () {
                $.magnificPopup.instance.close = function () {
                  // Lets set o cookie with expired  period.
                  var date = new Date();
                  date.setTime(date.getTime() + (48 * 3600 * 1000));
                  $.cookie("av_popup", true, {expires: date});
                  $.magnificPopup.proto.close.call(this);
                };
              }
            }
          });
        }, avPopup.delays.up * 1000);

        // Close popup after specific delay.
        setTimeout(function () {
          $.magnificPopup.close();
        }, avPopup.delays.up * 1000 + avPopup.delays.close * 1000);

      }
    }
  };

})(jQuery);
