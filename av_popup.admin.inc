<?php
/**
 * @file
 * Represents configuration forms and all logic related to them.
 *
 * 1) Delay in popup (when it comes up - seconds).
 * 2) Link - internal or external link.
 * 3) Session cookie reset.
 * 4) Delay in between when user last saw popup.
 * 5) Time for the popup to automatically close (seconds).
 * 6) Limit to global vs. page specific and page excluding.
 */

/**
 * Form handler for configuration page.
 *
 * @param array $form
 * @param array $form_state
 *
 * @return array
 */
function av_popup_settings_form($form, &$form_state) {
  $form['#tree'] = TRUE;

  $settings = variable_get('av_popup_settings', array());
  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Common settings of popup'),
    '#collapsible' => FALSE,
  );

  $form['settings']['delays'] = array(
    '#type' => 'fieldset',
    '#title' => t('Delays'),
    '#collapsible' => FALSE,
  );

  $form['settings']['delays']['up'] = array(
    '#type' => 'textfield',
    '#title' => t('Delay for comes up'),
    '#description' => t('Delay in popup (when it comes up - seconds).'),
    '#default_value' => isset($settings['delays']['up']) ? $settings['delays']['up'] : 1,
    '#element_validate' => array('element_validate_integer_positive'),
  );

  $form['settings']['delays']['between'] = array(
    '#type' => 'textfield',
    '#title' => t('Last saw delay.'),
    '#description' => t('Delay in between when user last saw popup (in hours).'),
    '#default_value' => isset($settings['delays']['between']) ? $settings['delays']['between'] / 3600 : 48,
    '#element_validate' => array('element_validate_integer_positive'),
  );

  $form['settings']['delays']['close'] = array(
    '#type' => 'textfield',
    '#title' => t('Before close delay.'),
    '#description' => t('Time for the popup to automatically close (seconds)'),
    '#default_value' => isset($settings['delays']['close']) ? $settings['delays']['close'] : 1,
    '#element_validate' => array('element_validate_integer_positive'),
  );

  $form['settings']['reset'] = array(
    '#type' => 'checkbox',
    '#title' => t('Session cookie reset'),
    '#description' => t('Indicates when session cookie should be reset.'),
    '#default_value' => isset($settings['reset']) ? $settings['reset'] : FALSE,
  );

  $form['settings']['link'] = array(
    '#type' => 'textfield',
    '#title' => t('Link for redirecting'),
    '#description' => t('Link - internal or external link'),
    '#default_value' => isset($settings['link']) ? $settings['link'] : FALSE,
    '#element_validate' => array('element_validate_url'),
  );

  $form['settings']['image'] = array(
    '#type' => 'managed_file',
    '#title' => t('Popup image'),
    '#default_value' => isset($settings['image']) ? $settings['image'] : FALSE,
    '#upload_location' => 'public://av_popup',
  );

  $form['settings']['filters'] = array(
    '#type' => 'fieldset',
    '#title' => t('Filters'),
    '#collapsible' => FALSE,
  );

  $form['settings']['filters']['visibility'] = array(
    '#type' => 'radios',
    '#title' => t('Show block on specific pages'),
    '#options' => array(
      'excluded' => t('All pages except those listed'),
      'allowed' => t('Only the listed pages'),
    ),
    '#default_value' => isset($settings['filters']['visibility']) ? $settings['filters']['visibility'] : 'excluded',
  );

  $form['settings']['filters']['pages'] = array(
    '#type' => 'textarea',
    '#title' => t('Show popup on specific pages'),
    '#default_value' => isset($settings['filters']['pages']) ? $settings['filters']['pages'] : '',
    '#description' => t("Specify pages by using their paths. Enter one path per line. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array(
      '%blog' => 'blog',
      '%blog-wildcard' => 'blog/*',
      '%front' => '<front>',
    )),
  );

  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save settings'),
  );

  return $form;
}

/**
 * Submit handler for configuration page.
 *
 * @param array $form
 * @param array $form_state
 */
function av_popup_settings_form_submit($form, &$form_state) {
  $values = $form_state['values'];

  // Save file.
  $file = file_load($values['settings']['image']);
  $file->status = FILE_STATUS_PERMANENT;
  file_save($file);
  file_usage_add($file, 'av_popup', 'av_popup', time());

  // Save settings.
  $values['settings']['delays']['between'] *= 3600;
  variable_set('av_popup_settings', $values['settings']);

  $form_state['rebuild'] = TRUE;
  drupal_set_message(t('Settings was successfully saved.'));
}


/**
 * Form element validation handler for integer elements that must be positive.
 */
function element_validate_url($element, &$form_state) {
  $value = $element['#value'];
  if (filter_var($value, FILTER_VALIDATE_URL) === FALSE) {
    form_error($element, t('%name must be a valid link.', array('%name' => $element['#title'])));
  }
}
