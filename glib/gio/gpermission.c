/*
 * Copyright © 2010 Codethink Limited
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the licence, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * Author: Ryan Lortie <desrt@desrt.ca>
 */

#include "config.h"

#include "gpermission.h"
#include "glibintl.h"


/**
 * SECTION:gpermission
 * @title: GPermission
 * @short_description: an object representing the permission to perform
 *                     a certain action
 *
 * A #GPermission represents the status of the caller's permission to
 * perform a certain action.
 *
 * You can query if the action is currently allowed and if it is
 * possible to acquire the permission so that the action will be allowed
 * in the future.
 *
 * There is also an API to actually acquire the permission and one to
 * release it.
 *
 * As an example, a #GPermission might represent the ability for the
 * user to write to a #GSettings object.  This #GPermission object could
 * then be used to decide if it is appropriate to show a "Click here to
 * unlock" button in a dialog and to provide the mechanism to invoke
 * when that button is clicked.
 **/

/**
 * GPermission:
 *
 * #GPermission is an opaque data structure and can only be accessed
 * using the following functions.
 **/

G_DEFINE_ABSTRACT_TYPE (GPermission, g_permission, G_TYPE_OBJECT)

struct _GPermissionPrivate
{
  gboolean allowed;
  gboolean can_acquire;
  gboolean can_release;
};

enum  {
  PROP_NONE,
  PROP_ALLOWED,
  PROP_CAN_ACQUIRE,
  PROP_CAN_RELEASE
};

/**
 * g_permission_acquire:
 * @permission: a #GPermission instance
 * @cancellable: a #GCancellable, or %NULL
 * @error: a pointer to a %NULL #GError, or %NULL
 * @returns: %TRUE if the permission was successfully acquired
 *
 * Attempts to acquire the permission represented by @permission.
 *
 * The precise method by which this happens depends on the permission
 * and the underlying authentication mechanism.  A simple example is
 * that a dialog may appear asking the user to enter their password.
 *
 * You should check with g_permission_get_can_acquire() before calling
 * this function.
 *
 * If the permission is acquired then %TRUE is returned.  Otherwise,
 * %FALSE is returned and @error is set appropriately.
 *
 * This call is blocking, likely for a very long time (in the case that
 * user interaction is required).  See g_permission_acquire_async() for
 * the non-blocking version.
 *
 * Since: 2.26
 */
gboolean
g_permission_acquire (GPermission   *permission,
                      GCancellable  *cancellable,
                      GError       **error)
{
  return G_PERMISSION_GET_CLASS (permission)
    ->acquire (permission, cancellable, error);
}

/**
 * g_permission_acquire_async:
 * @permission: a #GPermission instance
 * @cancellable: a #GCancellable, or %NULL
 * @callback: the #GAsyncReadyCallback to call when done
 * @user_data: the user data to pass to @callback
 *
 * Attempts to acquire the permission represented by @permission.
 *
 * This is the first half of the asynchronous version of
 * g_permission_acquire().
 *
 * Since: 2.26
 **/
void
g_permission_acquire_async (GPermission         *permission,
                            GCancellable        *cancellable,
                            GAsyncReadyCallback  callback,
                            gpointer             user_data)
{
  G_PERMISSION_GET_CLASS (permission)
    ->acquire_async (permission, cancellable, callback, user_data);
}

/**
 * g_permission_acquire_finish:
 * @permission: a #GPermission instance
 * @result: the #GAsyncResult given to the #GAsyncReadyCallback
 * @error: a pointer to a %NULL #GError, or %NULL
 * @returns: %TRUE if the permission was successfully acquired
 *
 * Collects the result of attempting to acquire the permission
 * represented by @permission.
 *
 * This is the second half of the asynchronous version of
 * g_permission_acquire().
 *
 * Since: 2.26
 **/
gboolean
g_permission_acquire_finish (GPermission   *permission,
                             GAsyncResult  *result,
                             GError       **error)
{
  return G_PERMISSION_GET_CLASS (permission)
    ->acquire_finish (permission, result, error);
}

/**
 * g_permission_release:
 * @permission: a #GPermission instance
 * @cancellable: a #GCancellable, or %NULL
 * @error: a pointer to a %NULL #GError, or %NULL
 * @returns: %TRUE if the permission was successfully released
 *
 * Attempts to release the permission represented by @permission.
 *
 * The precise method by which this happens depends on the permission
 * and the underlying authentication mechanism.  In most cases the
 * permission will be dropped immediately without further action.
 *
 * You should check with g_permission_get_can_release() before calling
 * this function.
 *
 * If the permission is released then %TRUE is returned.  Otherwise,
 * %FALSE is returned and @error is set appropriately.
 *
 * This call is blocking, likely for a very long time (in the case that
 * user interaction is required).  See g_permission_release_async() for
 * the non-blocking version.
 *
 * Since: 2.26
 **/
gboolean
g_permission_release (GPermission   *permission,
                      GCancellable  *cancellable,
                      GError       **error)
{
  return G_PERMISSION_GET_CLASS (permission)
    ->release (permission, cancellable, error);
}

/**
 * g_permission_release_async:
 * @permission: a #GPermission instance
 * @cancellable: a #GCancellable, or %NULL
 * @callback: the #GAsyncReadyCallback to call when done
 * @user_data: the user data to pass to @callback
 *
 * Attempts to release the permission represented by @permission.
 *
 * This is the first half of the asynchronous version of
 * g_permission_release().
 *
 * Since: 2.26
 **/
void
g_permission_release_async (GPermission         *permission,
                            GCancellable        *cancellable,
                            GAsyncReadyCallback  callback,
                            gpointer             user_data)
{
  G_PERMISSION_GET_CLASS (permission)
    ->release_async (permission, cancellable, callback, user_data);
}

/**
 * g_permission_release_finish:
 * @permission: a #GPermission instance
 * @result: the #GAsyncResult given to the #GAsyncReadyCallback
 * @error: a pointer to a %NULL #GError, or %NULL
 * @returns: %TRUE if the permission was successfully released
 *
 * Collects the result of attempting to release the permission
 * represented by @permission.
 *
 * This is the second half of the asynchronous version of
 * g_permission_release().
 *
 * Since: 2.26
 **/
gboolean
g_permission_release_finish (GPermission   *permission,
                             GAsyncResult  *result,
                             GError       **error)
{
  return G_PERMISSION_GET_CLASS (permission)
    ->release_finish (permission, result, error);
}

/**
 * g_permission_get_allowed:
 * @permission: a #GPermission instance
 * @returns: the value of the 'allowed' property
 *
 * Gets the value of the 'allowed' property.  This property is %TRUE if
 * the caller currently has permission to perform the action that
 * @permission represents the permission to perform.
 *
 * Since: 2.26
 **/
gboolean
g_permission_get_allowed (GPermission *permission)
{
  return permission->priv->allowed;
}

/**
 * g_permission_get_can_acquire:
 * @permission: a #GPermission instance
 * @returns: the value of the 'can-acquire' property
 *
 * Gets the value of the 'can-acquire' property.  This property is %TRUE
 * if it is generally possible to acquire the permission by calling
 * g_permission_acquire().
 *
 * Since: 2.26
 **/
gboolean
g_permission_get_can_acquire (GPermission *permission)
{
  return permission->priv->can_acquire;
}

/**
 * g_permission_get_can_release:
 * @permission: a #GPermission instance
 * @returns: the value of the 'can-release' property
 *
 * Gets the value of the 'can-release' property.  This property is %TRUE
 * if it is generally possible to release the permission by calling
 * g_permission_release().
 *
 * Since: 2.26
 **/
gboolean
g_permission_get_can_release (GPermission *permission)
{
  return permission->priv->can_release;
}

/**
 * g_permission_impl_update:
 * @permission: a #GPermission instance
 * @allowed: the new value for the 'allowed' property
 * @can_acquire: the new value for the 'can-acquire' property
 * @can_release: the new value for the 'can-release' property
 *
 * This function is called by the #GPermission implementation to update
 * the properties of the permission.  You should never call this
 * function except from a #GPermission implementation.
 *
 * GObject notify signals are generated, as appropriate.
 *
 * Since: 2.26
 **/
void
g_permission_impl_update (GPermission *permission,
                          gboolean     allowed,
                          gboolean     can_acquire,
                          gboolean     can_release)
{
  GObject *object = G_OBJECT (permission);

  g_object_freeze_notify (object);

  if (allowed != permission->priv->allowed)
    {
      permission->priv->allowed = !!allowed;
      g_object_notify (object, "allowed");
    }

  if (can_acquire != permission->priv->can_acquire)
    {
      permission->priv->can_acquire = !!can_acquire;
      g_object_notify (object, "can-acquire");
    }

  if (can_release != permission->priv->can_release)
    {
      permission->priv->can_release = !!can_release;
      g_object_notify (object, "can-release");
    }

  g_object_thaw_notify (object);
}

static void
g_permission_get_property (GObject *object, guint prop_id,
                           GValue *value, GParamSpec *pspec)
{
  GPermission *permission = G_PERMISSION (object);

  switch (prop_id)
    {
    case PROP_ALLOWED:
      g_value_set_boolean (value, permission->priv->allowed);
      break;

    case PROP_CAN_ACQUIRE:
      g_value_set_boolean (value, permission->priv->can_acquire);
      break;

    case PROP_CAN_RELEASE:
      g_value_set_boolean (value, permission->priv->can_release);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
  }
}

static void
g_permission_init (GPermission *permission)
{
  permission->priv = G_TYPE_INSTANCE_GET_PRIVATE (permission,
                                                  G_TYPE_PERMISSION,
                                                  GPermissionPrivate);
}

static void
g_permission_class_init (GPermissionClass *class)
{
  GObjectClass *object_class = G_OBJECT_CLASS (class);

  object_class->get_property = g_permission_get_property;

  /**
   * GPermission:allowed:
   *
   * %TRUE if the caller currently has permission to perform the action that
   * @permission represents the permission to perform.
   */
   g_object_class_install_property (object_class, PROP_ALLOWED,
     g_param_spec_boolean ("allowed",
                           P_("Is allowed"),
                           P_("If the caller is allowed to perform the action"),
                           FALSE,
                           G_PARAM_STATIC_STRINGS | G_PARAM_READABLE));

  /**
   * GPermission:can-acquire:
   *
   * %TRUE if it is generally possible to acquire the permission by calling
   * g_permission_acquire().
   */
   g_object_class_install_property (object_class, PROP_CAN_ACQUIRE,
     g_param_spec_boolean ("can-acquire",
                           P_("Can acquire"),
                           P_("If calling g_permission_acquire() makes sense"),
                           FALSE,
                           G_PARAM_STATIC_STRINGS | G_PARAM_READABLE));

  /**
   * GPermission:can-release:
   *
   * %TRUE if it is generally possible to release the permission by calling
   * g_permission_release().
   */
   g_object_class_install_property (object_class, PROP_CAN_RELEASE,
     g_param_spec_boolean ("can-release",
                           P_("Can release"),
                           P_("If calling g_permission_release() makes sense"),
                           FALSE,
                           G_PARAM_STATIC_STRINGS | G_PARAM_READABLE));

  g_type_class_add_private (class, sizeof (GPermissionPrivate));
}
